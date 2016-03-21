#ifndef UNITTEST_FUNCTIONS
#define UNITTEST_FUNCTIONS

#include <string>
#include <algorithm>
#include <functional>

class Test {
    bool passed = true;
    std::string name;
    std::vector<std::string> failedInputs;
    public:
        Test(std::string funcName) : name(funcName) {}
        std::function<void()> run;

        std::string getName() { return this->name; }
        void fail(std::string input) { this->passed = false; this->failedInputs.push_back(input); }
        bool hasPassed() { return this->passed; }
        std::vector<std::string>::iterator getFailedStart() { return this->failedInputs.begin(); }
        std::vector<std::string>::iterator getFailedEnd() { return this->failedInputs.end(); }
};

void runTest(Test func());

bool equals(double value1, double value2, double epsilon);

// Helper macro to initialise test case
#define TEST_CASE(Name) \
Test Name() { \
    Test test(#Name); \
    test.run = [&test]

#define END_TEST ; return test; }

#endif
