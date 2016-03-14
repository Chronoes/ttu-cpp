#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

bool checktime(std::string timeString) {
    if (timeString[0] == ' ') {
        timeString = timeString.substr(1, 0);
    }

    size_t i;
    std::vector<std::string> components;
    std::string current = "";
    for (i = 0; i < timeString.length(); i++) {
        switch (char nr = timeString[i]) {
        case '.':
        case ',':
        case ':':
            components.push_back(current);
            break;
        default:
            current += nr;
            break;
        }
    }

    std::vector<int>

    for (auto it = components.begin(); it != components.end(); it++) {
        auto str = *it;
        for (i = 0; i < str.length(); i++) {
            if (!std::isdigit(str[i])) {
                return false;
            }

        }
    }

    switch (components.size()) {
        case 2:
            break;
    }
    return false;
}

double ctime(std::string str, char unit = 's') {
    return 0.0;
}

int main(int argc, char const *argv[]) {
    return 0;
}
