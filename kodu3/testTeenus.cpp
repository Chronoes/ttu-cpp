#include <map>
#include <string>
#include <ctime>

#include "unittest.hpp"
#include "Teenus.hpp"

TEST_CASE(GetDay) {
    std::map<char, Day> cases = {
        {'E', Day::Monday},
        {'T', Day::Tuesday},
        {'K', Day::Wednesday},
        {'N', Day::Thursday},
        {'R', Day::Friday},
        {'L', Day::Saturday},
        {'P', Day::Sunday},
        {'U', Day::Invalid},
        {'e', Day::Invalid},
        {'0', Day::Invalid}
    };

    for (auto element : cases) {
        if (getDay(element.first) != element.second) {
            test.fail(std::to_string(static_cast<char>(element.first)));
        }
    }
} END_TEST

TEST_CASE(ParseDayRange) {
    std::map<std::string, std::pair<Day, Day>> cases = {
        {"E", {Day::Monday, Day::None}},
        {"T R", {Day::Tuesday, Day::Friday}},
        {"P-K", {Day::Sunday, Day::Wednesday}},
        {"N-S", {Day::Thursday, Day::Invalid}},
        {"1-7", {Day::Invalid, Day::Invalid}}
    };

    for (auto element : cases) {
        if (parseDayRange(element.first) != element.second) {
            test.fail(element.first);
        }
    }
} END_TEST

TEST_CASE(Teenus_constructor_serviceName) {
    auto service = new Teenus("name");
    if (service->nimi() != "name") {
        test.fail(service->nimi());
    }
} END_TEST

TEST_CASE(Teenus_constructor_serviceName_start_end) {
    auto service = new Teenus("name", 7.5, 18.5);
    for (auto element : service->openTimes) {
        auto range = element.second;
        auto expected = new TimeRange(7.5, 18.5);
        if (*range != *expected) {
            char str[200];
            std::sprintf(str, "%c: %f, %f", element.first, range->start, range->end);
            test.fail(str);
        }
    }
} END_TEST

TEST_CASE(Teenus_constructor_serviceName_range_start_end) {
    auto service = new Teenus("name", "E-R", 10, 0);
    for (auto element : service->openTimes) {
        auto range = element.second;
        if (element.first == Day::Saturday || element.first == Day::Sunday) {
            auto expected = new TimeRange(0, 0);
            if (*range != *expected) {
                char str[200];
                std::sprintf(str, "%c: %f, %f", element.first, range->start, range->end);
                test.fail(str);
            }
        } else {
            auto expected = new TimeRange(10, 0);
            if (*range != *expected) {
                char str[200];
                std::sprintf(str, "%c: %f, %f", element.first, range->start, range->end);
                test.fail(str);
            }
        }
    }
} END_TEST

TEST_CASE(Paev) {
    auto service = new Teenus("name");
    service->paev('T', 3.25, 12);
    auto range = service->openTimes[Day::Tuesday];
    auto expected = new TimeRange(3.25, 12);
    if (*range != *expected) {
        char str[200];
        std::sprintf(str, "%f, %f", range->start, range->end);
        test.fail(str);
    }
} END_TEST

TEST_CASE(Tunnid) {
    auto service = new Teenus("name", "E-R", 9, 17);
    if (!equals(service->tunnid(), 40, 1e-3)) {
        test.fail("E-R: 9, 17 == " + std::to_string(service->tunnid()));
    }
} END_TEST

TEST_CASE(Onavatud) {
    time_t _currentTime;
    std::time(&_currentTime);
    auto currentTime = std::localtime(&_currentTime);
    auto service = new Teenus("name", currentTime->tm_hour - 1, currentTime->tm_hour + 1);
    if (!service->onavatud()) {
        char str[200];
        std::sprintf(str, "%f, %f", (double) currentTime->tm_hour - 1, (double) currentTime->tm_hour + 1);
        test.fail(str);
    }
} END_TEST

TEST_CASE(OperatorGreaterThan) {
    auto service = new Teenus("name", "E-R", 9, 17);
    auto service2 = new Teenus("name", "E-R", 9, 16);
    if (!(service > service2)) {
        char str[200];
        std::sprintf(str, "%f, %f", range->start, range->end);
        test.fail()
    }
} END_TEST

int main(int argc, char const *argv[]) {
    runTest(GetDay);
    runTest(ParseDayRange);
    runTest(Teenus_constructor_serviceName);
    runTest(Teenus_constructor_serviceName_start_end);
    runTest(Teenus_constructor_serviceName_range_start_end);
    runTest(Paev);
    runTest(Tunnid);
    runTest(Onavatud);
    runTest(OperatorGreaterThan);
    return 0;
}
