#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>

#include "unittest.hpp"

std::string wrapString(std::string toWrap, char wrapper, size_t fullLength) {
    std::string wrapperString = std::string((fullLength - toWrap.length()) / 2, wrapper);
    return wrapperString + toWrap + wrapperString;
}

void runTest(Test func()) {
    Test result = func();
    result.run();
    std::cout << result.getName() << "()";
    if (result.hasPassed()) {
        std::cout << " -- PASS";
    } else {
        std::cout << " -- FAIL" << std::endl;
        std::stringstream inputs;
        size_t maxLength = 0;
        for (auto iter = result.getFailedStart(); iter != result.getFailedEnd(); iter++) {
            std::string tmp = "| Input: '" + *iter + "'";
            if (tmp.length() > maxLength) maxLength = tmp.length();
            inputs << tmp << std::endl;
        }
        if (maxLength % 2) maxLength++;
        std::cout << wrapString(" Failed ", '-', maxLength) << std::endl << inputs.str() << std::string(maxLength, '-');
    }
    std::cout << std::endl;
}
