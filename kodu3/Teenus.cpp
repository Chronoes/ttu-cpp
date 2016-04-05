#include <ctime>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cmath>

#include "Teenus.hpp"

inline bool equals(double value1, double value2, double epsilon) {
    return std::fabs(value1 - value2) <= epsilon;
}

std::vector<Day> DayRange = {
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday,
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};

Day getDay(char day) {
    auto iter = std::find(DayRange.cbegin(), DayRange.cend(), static_cast<Day>(day));
    if (iter == DayRange.end()) {
        return Day::Invalid;
    }
    return *iter;
}

std::pair<Day, Day> parseDayRange(std::string range) {
    if (range.length() == 3) {
        return std::pair<Day, Day>(getDay(range[0]), getDay(range[2]));
    } else if (range.length() == 0) {
        return std::pair<Day, Day>(Day::Invalid, Day::Invalid);
    }
    return std::pair<Day, Day>(getDay(range[0]), None);
}


TimeRange::TimeRange() : start(0), end(0) {}

TimeRange::TimeRange(double _start, double _end) :
start(std::fmod(std::fabs(_start), 24)), end(std::fmod(std::fabs(_end), 24)) {}

bool TimeRange::inRange(double hours) {
    return this->start <= hours && hours <= this->end;
}

bool TimeRange::operator==(TimeRange& range) {
    return equals(this->start, range.start, 1e-3) && equals(this->end, range.end, 1e-3);
}

bool TimeRange::operator!=(TimeRange& range) {
    return !this->operator==(range);
}


Teenus::Teenus(std::string serviceName) : Teenus(serviceName, 0, 0) {}

Teenus::Teenus(std::string serviceName, double start, double end) : name(serviceName) {
    this->initOpenTimes({start, end});
}

Teenus::Teenus(std::string serviceName, std::string dayRange, double start, double end) : Teenus(serviceName) {
    auto parsed = parseDayRange(dayRange);
    TimeRange timeRange = {start, end};
    if (parsed.first != Day::Invalid && parsed.second != Day::Invalid) {
        if (parsed.second == Day::None) {
            this->setOpenTime(parsed.first, timeRange);
        } else {
            auto iter = std::find(DayRange.cbegin(), DayRange.cend(), parsed.first);
            do {
                this->setOpenTime(*iter, timeRange);
            } while (*iter++ != parsed.second);
        }
    }
}



void Teenus::initOpenTimes(TimeRange range) {
    this->openTimes = std::map<Day, TimeRange*> {
        {Day::Monday, new TimeRange(range.start, range.end)},
        {Day::Tuesday, new TimeRange(range.start, range.end)},
        {Day::Wednesday, new TimeRange(range.start, range.end)},
        {Day::Thursday, new TimeRange(range.start, range.end)},
        {Day::Friday, new TimeRange(range.start, range.end)},
        {Day::Saturday, new TimeRange(range.start, range.end)},
        {Day::Sunday, new TimeRange(range.start, range.end)}
    };
}

void Teenus::setOpenTime(Day day, TimeRange range) {
    this->openTimes[day] = new TimeRange(range.start, range.end);
}

const std::string Teenus::nimi() {
    return this->name;
}

void Teenus::paev(char day, double start, double end) {
    auto parsed = getDay(day);
    if (parsed != Day::Invalid) {
        this->setOpenTime(parsed, {start, end});
    }
}

double Teenus::tunnid() {
    return std::accumulate(this->openTimes.begin(), this->openTimes.end(), 0.0,
    [](double carry, std::pair<Day, TimeRange*> next) {
        auto timeRange = next.second;
        if (timeRange->end < timeRange->start) {
            carry += 24;
        }
        return carry + timeRange->end - timeRange->start;
    });
}

inline double convertToHoursFrom(std::tm* timeStruct) {
    return static_cast<double>(timeStruct->tm_hour) + static_cast<double>(timeStruct->tm_min) / 60 + static_cast<double>(timeStruct->tm_sec) / 3600;
}

bool Teenus::onavatud() {
    time_t _currentTime;
    std::time(&_currentTime);
    auto currentTime = std::localtime(&_currentTime);

    auto it = DayRange.cbegin();
    std::advance(it, currentTime->tm_wday + 1);
    auto timeRange = this->openTimes.at(*it);
    return timeRange->inRange(convertToHoursFrom(currentTime));
}

bool Teenus::operator> (Teenus& otherService) {
    return this->tunnid() - otherService.tunnid() > 1e3;
}
