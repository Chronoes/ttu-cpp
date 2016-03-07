#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#define CORRECT_CODE 0
#define WRONG_LENGTH 1
#define WRONG_SYMBOLS 2
#define WRONG_FIRST_NUMBER 4
#define WRONG_MONTH 8
#define WRONG_DAY_COUNT 16
#define WRONG_CHECKSUM 32

int getDayCount(int month, int year) {
    switch (month) {
        case 2:
            return year % 4 ? 28 : 29;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
    }
    return 31;
}

int checkSum(std::string idCode, bool recheck) {
    auto sum = 0;
    auto weight = recheck ? 3 : 1;
    for (size_t i = 0; i < idCode.length() - 1; i++) {
        auto increment = (weight + i) % 10;
        if (increment == 0) {
            weight++;
            increment++;
        }
        sum += std::atoi(idCode.substr(i, i + 1).c_str()) * increment;
    }
    auto remainder = sum % 11;
    if (!recheck && remainder == 10) {
        return checkSum(idCode, true);
    }
    return remainder % 10;
}

int checkSum(std::string idCode) {
    return checkSum(idCode, false);
}

int checkId(std::string idCode) {
    if (idCode.length() != 11) {
        return WRONG_LENGTH;
    } else if (!std::all_of(idCode.begin(), idCode.end(), ::isdigit)) {
        return WRONG_SYMBOLS;
    }

    auto error = CORRECT_CODE;
    auto first = std::atoi(idCode.substr(0, 1).c_str());
    if (first < 1 || first > 6) {
        error += WRONG_FIRST_NUMBER;
    }

    auto month = std::atoi(idCode.substr(3, 2).c_str());
    if (month < 1 || month > 12) {
        error += WRONG_MONTH;
    }

    auto day = std::atoi(idCode.substr(5, 2).c_str());
    if (day < 1 || day > getDayCount(month, std::atoi(idCode.substr(1, 2).c_str()))) {
        error += WRONG_DAY_COUNT;
    }

    if (checkSum(idCode) != std::atoi(idCode.substr(10, 1).c_str())) {
        error += WRONG_CHECKSUM;
    }
    return error;
}

int main(int argc, char const *argv[]) {
    int result;
    if (argc > 1) {
        result = checkId(std::string(argv[1]));
    } else {
        std::string code;
        std::cout << "Insert ID code: ";
        std::cin >> code;
        result = checkId(code);
    }

    std::map<const int, const char*> errorMessages;
    errorMessages[WRONG_LENGTH] = "ID code is not 11 digits long.";
    errorMessages[WRONG_SYMBOLS] = "ID code must be all digits.";
    errorMessages[WRONG_FIRST_NUMBER] = "First number must be between 1 and 6 inclusive.";
    errorMessages[WRONG_MONTH] = "Month must be between 01 and 12 inclusive.";
    errorMessages[WRONG_DAY_COUNT] = "Day count is wrong for given month.";
    errorMessages[WRONG_CHECKSUM] = "ID code checksum is invalid.";

    if (result == CORRECT_CODE) {
        std::cout << "ID code is correct." << std::endl;
    } else {
        for (auto& message : errorMessages) {
            if (result & message.first) {
                std::cout << message.second << std::endl;
            }
        }
    }
    std::cout << result;

    return 0;
}
