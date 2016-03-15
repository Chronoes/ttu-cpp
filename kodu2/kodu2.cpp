#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
// #include <stdio.h>
#include "kodu2.h"

bool splitTimeString(std::string timeString, std::vector<std::string>& components) {
    if (timeString[0] == ' ') {
        timeString = timeString.substr(1, 0);
    }

    std::vector<std::string> stringComponents;
    std::string current = "";
    bool hasMillis = false;
    for (size_t i = 0; i < timeString.length(); i++) {
        switch (char nr = timeString[i]) {
        case '.':
        case ',':
            if (hasMillis) {
                return false;
            }
            hasMillis = true;
        case ':':
            if (current.length() == 0) {
                return false;
            }

            #if DEBUG
            std::cout << "'" << current << "' ";
            #endif

            stringComponents.push_back(current);
            current = hasMillis ? "." : "";
            break;
        default:
            if (!std::isdigit(nr)) {
                return false;
            }
            current += nr;
            break;
        }
    }

    if (current.length() == 0) {
        return false;
    }
    stringComponents.push_back(current);

    #if DEBUG
    std::cout << "'" << current << "' ";
    std::cout << "size:" << stringComponents.size() << std::endl;
    #endif
    if (stringComponents.size() > 0 && stringComponents.size() < 5) {
        components.assign(stringComponents.begin(), stringComponents.end());
        return true;
    }
    return false;
}

bool checktime(std::string timeString, std::vector<std::string> parsedComponents) {
    if (parsedComponents.size() == 0) {
        return false;
    }
    const auto last = parsedComponents.back();
    if (last[0] == '.') {
        if (last.length() != 4) {
            return false;
        }
        parsedComponents.pop_back();
    }

    for (size_t i = 1; i < parsedComponents.size(); i++) {
        if (parsedComponents[i].length() != 2 || std::atoi(parsedComponents[i].c_str()) >= 60) {
            return false;
        }
    }
    return true;
}

bool checktime(std::string timeString) {
    std::vector<std::string> components;
    return splitTimeString(timeString, components) && checktime(timeString, components);
}

double ctime(std::string timeString, char unit) {
    #if DEBUG
    std::cout << "Unit: " << unit << std::endl;
    #endif

    if (unit != 's' && unit != 'm' && unit != 'h') {
        return -1;
    }
    std::vector<std::string> components;
    if (!splitTimeString(timeString, components) || !checktime(timeString, components)) {
        return -1;
    }

    double value = 0;
    auto iter = components.rbegin();
    if ((*iter)[0] == '.') {
        value += (double) std::atoi((*iter).substr(1, -1).c_str()) / 1e+3;
        iter++;
    }

    #if DEBUG
    std::cout << "Milliseconds: " << value << std::endl;
    #endif

    int i = 0;
    if (unit == 'm') {
        i = -1;
        value /= 60.0;
    } else if (unit == 'h') {
        i = -2;
        value /= 3600.0;
    }

    for (; iter != components.rend(); iter++, i++) {
        value += std::atoi((*iter).c_str()) * pow(60, i);
    }
    return value;
}

std::string stime(const double seconds) {
    char result[128];
    std::sprintf(result, "%d:%02d:%06.3f", (int) (seconds / 3600), (int) (seconds / 60) % 60, ((int) seconds % 60) + seconds - (int) seconds);
    return result;
}

#ifndef TESTING
int main(int argc, char const *argv[]) {
    return 0;
}
#endif
