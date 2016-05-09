#include <ctime>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cmath>

#include "Saade.hpp"
#include "../kodu2/kodu2.h"

Saade::Saade(std::string _name, std::string _date) : name(_name), date(_date) {}

void Saade::setRunTime(std::string start, std::string end, bool nextDay) {
    runTime.first = start;
    runTime.second = (nextDay ? 24 * 60 : 0) + ctime(end) - ctime(start);
}

const std::string Saade::getName() {
    return name;
}

const std::string Saade::getDate() {
    return date;
}

TimeRange Saade::getRunTime() {
    return runTime;
}

TimeRange Saade::getOriginalRunTime() {
    return TimeRange("", 0);
}

const std::string Saade::getStartTime() {
    return runTime.first;
}

double Saade::getLength() {
    return runTime.second;
}

bool Saade::isRepeatingShow() {
    return isRepeat;
}

Kordussaade::Kordussaade(std::string name, std::string date) : Saade(name, date) {
    isRepeat = true;
}
Kordussaade::Kordussaade(std::string name, std::string date, TimeRange _originalRunTime) : Saade(name, date), originalRunTime(_originalRunTime) {
    isRepeat = true;
}

const std::string Kordussaade::getName() {
    return Saade::getName() + " (Kordus" + (originalRunTime.second > 0 ? ", originaal " + originalRunTime.first : "") + ")";
}

TimeRange Kordussaade::getOriginalRunTime() {
    return originalRunTime;
}
