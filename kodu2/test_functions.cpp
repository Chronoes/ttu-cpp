#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>

#include "test_functions.h"

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
