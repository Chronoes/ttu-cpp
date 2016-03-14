#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <math.h>
#include "kodu2.h"

typedef struct testfunc_t {
    bool passed = true;
    std::string name;
    std::vector<std::string> failedInputs;
    testfunc_t(std::string funcName) : name(funcName) {}
} TestFunc;

bool deepEqual(std::vector<std::string> expected, std::vector<std::string> actual) {
    if (actual.size() != expected.size()) return false;
    for (size_t i = 0; i < actual.size(); i++) {
        if (actual[i] != expected[i]) return false;
    }
    return true;
}

bool equals(double value1, double value2, double epsilon) {
    return fabs(value1 - value2) <= epsilon;
}

TestFunc testSplitToComponents() {
    TestFunc func(__FUNCTION__);

    std::map<std::string, std::vector<std::string>> cases;
    cases["90.351"] = std::vector<std::string>({"90", ".351"});
    cases["33:50.120"] = std::vector<std::string>({"33", "50", ".120"});
    cases["1322:10:23.999"] = std::vector<std::string>({"1322", "10", "23", ".999"});
    cases["850"] = std::vector<std::string>({"850"});
    cases["90:30"] = std::vector<std::string>({"90", "30"});
    cases["30:22,231"] = std::vector<std::string>({"30", "22", ".231"});

    std::vector<std::string> components;
    for (auto& testCase : cases) {
        if (!(splitTimeString(testCase.first, components) && deepEqual(testCase.second, components))) {
            func.passed = false;
            func.failedInputs.push_back(testCase.first);
        }
        components.clear();
    }
    return func;
}

TestFunc testSplitToComponentsFaulty() {
    TestFunc func(__FUNCTION__);

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
            func.passed = false;
            func.failedInputs.push_back(cases[i]);
        }
        components.clear();
    }
    return func;
}

TestFunc testCheckTime() {
    TestFunc func(__FUNCTION__);

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
            func.passed = false;
            func.failedInputs.push_back(cases[i]);
        }
    }
    return func;
}

TestFunc testCheckTimeFaulty() {
    TestFunc func(__FUNCTION__);

    std::vector<std::string> cases({
        "15:60",
        "300:3",
        "20:5:59",
        "4002:02:19,23",
        "30.3"
    });

    for (size_t i = 0; i < cases.size(); i++) {
        if (checktime(cases[i])) {
            func.passed = false;
            func.failedInputs.push_back(cases[i]);
        }
    }
    return func;
}

TestFunc testConvertTime_second() {
    TestFunc func(__FUNCTION__);

    std::map<std::string, double> cases;
    cases["90.351"] = 90.351;
    cases["33:50.120"] = 33 * 60 + 50.120;
    cases["1322:10:23.999"] = 1322 * 3600 + 10 * 60 + 23.999;
    cases["850"] = 850;
    cases["90:30"] = 90 * 60 + 30;
    cases["30:22,231"] = 30 * 60 + 22.231;

    for (auto& testCase : cases) {
        if (equals(ctime(testCase.first), testCase.second, 1e-3)) {
            func.passed = false;
            func.failedInputs.push_back(testCase.first);
        }
    }
    return func;
}

std::string wrapString(std::string toWrap, char wrapper, size_t fullLength) {
    std::string wrapperString = std::string((fullLength - toWrap.length()) / 2, wrapper);
    return wrapperString + toWrap + wrapperString;
}

void runTest(TestFunc func()) {
    TestFunc result = func();
    std::cout << result.name << "()";
    if (result.passed) {
        std::cout << " -- PASS";
    } else {
        std::cout << " -- FAIL" << std::endl;
        std::stringstream inputs;
        size_t maxLength = 0;
        for (size_t i = 0; i < result.failedInputs.size(); i++) {
            std::string tmp = "| Input: '" + result.failedInputs[i] + "'";
            if (tmp.length() > maxLength) maxLength = tmp.length();
            inputs << tmp << std::endl;
        }
        if (maxLength % 2) maxLength++;
        std::cout << wrapString(" Failed ", '-', maxLength) << std::endl << inputs.str() << std::string(maxLength, '-');
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
    runTest(testSplitToComponents);
    runTest(testSplitToComponentsFaulty);
    runTest(testCheckTime);
    runTest(testCheckTimeFaulty);
    runTest(testConvertTime_second);
    return 0;
}
