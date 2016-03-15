#ifndef TEST_FUNCTIONS
#define TEST_FUNCTIONS

#include <string>
#include <algorithm>

typedef struct testfunc_t {
    bool passed = true;
    std::string name;
    std::vector<std::string> failedInputs;
    testfunc_t(std::string funcName) : name(funcName) {}
} TestFunc;

void runTest(TestFunc func());

bool deepEqual(std::vector<std::string> expected, std::vector<std::string> actual);

bool equals(double value1, double value2, double epsilon);

#endif
