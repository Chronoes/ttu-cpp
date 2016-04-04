#include <map>
#include <string>
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
        if (!equals(range.start, 7.5, 1e-3) || !equals(range.end, 18.5, 1e-3)) {
            char str[200];
            std::sprintf(str, "%c: %f, %f", element.first, range.start, range.end);
            test.fail(str);
        }
    }
} END_TEST

TEST_CASE(Teenus_constructor_serviceName_range_start_end) {
    auto service = new Teenus("name", "E-R", 10, 0);
    for (auto element : service->openTimes) {
        auto range = element.second;
        if (element.first == Day::Saturday || element.first == Day::Sunday) {
            if (!equals(range.start, 0, 1e-3) || !equals(range.end, 0, 1e-3)) {
                char str[200];
                std::sprintf(str, "%c: %f, %f", element.first, range.start, range.end);
                test.fail(str);
            }
        } else {
            if (!equals(range.start, 10, 1e-3) || !equals(range.end, 0, 1e-3)) {
                char str[200];
                std::sprintf(str, "%c: %f, %f", element.first, range.start, range.end);
                test.fail(str);
            }
        }
    }
} END_TEST



int main(int argc, char const *argv[]) {
    runTest(GetDay);
    runTest(ParseDayRange);
    runTest(Teenus_constructor_serviceName);
    runTest(Teenus_constructor_serviceName_start_end);
    runTest(Teenus_constructor_serviceName_range_start_end);
    return 0;
}
