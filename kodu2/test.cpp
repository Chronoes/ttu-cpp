#include <map>
#include <algorithm>

#include "test_functions.h"
#include "kodu2.h"

TEST_CASE(SplitToComponents) {
    std::map<std::string, std::vector<std::string>> cases;
    cases["90.351"] = std::vector<std::string>({"90", ".351"});
    cases["33:50.120"] = std::vector<std::string>({"33", "50", ".120"});
    cases["1322:10:23.999"] = std::vector<std::string>({"1322", "10", "23", ".999"});
    cases["850"] = std::vector<std::string>({"850"});
    cases["90:30"] = std::vector<std::string>({"90", "30"});
    cases["30:22,231"] = std::vector<std::string>({"30", "22", ".231"});

    std::vector<std::string> components;
    for (auto& testCase : cases) {
        if (splitTimeString(testCase.first, components) && testCase.second != components) {
            test.fail(testCase.first);
        }
        components.clear();
    }
} END_TEST

TEST_CASE(SplitToComponentsFaulty) {
    std::vector<std::string> cases({
        "",
        ".356",
        "90:",
        "150::23:13.12",
        ":13:23",
        "133:23:14.231.2",
        "22:2.323:231.145",
        "583:340:32:23:231.233",
        "03:a5:22"
    });

    std::vector<std::string> components;
    for (size_t i = 0; i < cases.size(); i++) {
        if (splitTimeString(cases[i], components)) {
            test.fail(cases[i]);
        }
        components.clear();
    }
} END_TEST

TEST_CASE(CheckTime) {
    std::vector<std::string> cases({
        "200",
        "15:30",
        "300:30",
        "20:59:59",
        "4002:02:19",
        "30.330",
        "23:01,000",
        "11:09:24.888",
        "123121:50:10,132"
    });

    for (size_t i = 0; i < cases.size(); i++) {
        if (!checktime(cases[i])) {
            test.fail(cases[i]);
        }
    }
} END_TEST

TEST_CASE(CheckTimeFaulty) {
    std::vector<std::string> cases({
        "15:60",
        "300:3",
        "20:5:59",
        "4002:02:19,23",
        "30.3"
    });

    for (size_t i = 0; i < cases.size(); i++) {
        if (checktime(cases[i])) {
            test.fail(cases[i]);
        }
    }
} END_TEST

TEST_CASE(ConvertTime_seconds) {
    std::map<std::string, double> cases;
    cases["90.351"] = 90.351;
    cases["33:50.120"] = 33 * 60 + 50.120;
    cases["1322:10:23.999"] = 1322 * 3600 + 10 * 60 + 23.999;
    cases["850"] = 850;
    cases["90:30"] = 90 * 60 + 30;
    cases["30:22,231"] = 30 * 60 + 22.231;

    for (auto& testCase : cases) {
        double result = ctime(testCase.first);
        if (result == -1 || !equals(result, testCase.second, 1e-3)) {
            test.fail(testCase.first);
        }
    }
    return test;
} END_TEST

TEST_CASE(ConvertTime_minutes) {
    std::map<std::string, double> cases;
    cases["90.351"] = 90.351 / 60.0;
    cases["33:50.120"] = 33 + 50.120 / 60.0;
    cases["1322:10:23.999"] = 1322 * 60 + 10 + 23.999 / 60.0;
    cases["850"] = 850 / 60.0;
    cases["90:30"] = 90 + 30 / 60.0;
    cases["30:22,231"] = 30 + 22.231 / 60.0;

    for (auto& testCase : cases) {
        double result = ctime(testCase.first, 'm');
        if (result == -1 || !equals(result, testCase.second, 1e-3)) {
            test.fail(testCase.first);
        }
    }
} END_TEST

TEST_CASE(ConvertTime_hours) {
    std::map<std::string, double> cases;
    cases["90.351"] = 90.351 / 3600.0;
    cases["33:50.120"] = 33 / 60.0 + 50.120 / 3600.0;
    cases["1322:10:23.999"] = 1322 + 10 / 60.0 + 23.999 / 3600.0;
    cases["850"] = 850 / 3600.0;
    cases["90:30"] = 90 / 60.0 + 30 / 3600.0;
    cases["30:22,231"] = 30 / 60.0 + 22.231 / 3600.0;

    for (auto& testCase : cases) {
        double result = ctime(testCase.first, 'h');
        if (result == -1 || !equals(result, testCase.second, 1e-3)) {
            test.fail(testCase.first);
        }
    }
} END_TEST

TEST_CASE(FormatTime) {
    std::map<double, std::string> cases;
    cases[90.351] = "0:01:30.351";
    cases[33 * 60 + 50.120] = "0:33:50.120";
    cases[1322 * 3600 + 10 * 60 + 23.999] = "1322:10:23.999";
    cases[850] = "0:14:10.000";
    cases[90 * 60 + 30] = "1:30:30.000";
    cases[30 * 60 + 22.231] = "0:30:22.231";
    cases[58 * 60 + 1.02] = "0:58:01.020";

    for (auto& testCase : cases) {
        if (stime(testCase.first) != testCase.second) {
            test.fail(std::to_string(testCase.first));
        }
    }
    return test;
} END_TEST
#include <iostream>
int main(int argc, char const *argv[]) {
    runTest(SplitToComponents);
    runTest(SplitToComponentsFaulty);
    runTest(CheckTime);
    runTest(CheckTimeFaulty);
    runTest(ConvertTime_seconds);
    runTest(ConvertTime_minutes);
    runTest(ConvertTime_hours);
    runTest(FormatTime);
    return 0;
}
