#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <algorithm>

std::map<std::string, std::string> States;

typedef struct result_t {
    std::string result;
    bool isCode, found = true;
} Result;

std::string findNameMatch(std::string searchString) {
    std::string match;
    for (auto state : States) {
        size_t diff;
        size_t length;
        if (searchString.length() < state.second.length()) {
            diff = state.second.length() - searchString.length();
            length = searchString.length();
        } else {
            diff = searchString.length() - state.second.length();
            length = state.second.length();
        }
        for (size_t i = 0; i < length; i++) {
            if (searchString[i] != state.second[i]) {
                diff++;
            }
            if (diff > 3) {
                break;
            }
        }
        if (diff <= 3) {
            match = state.first;
            break;
        }
    }
    return match;
}

Result getResult(std::string searchString) {
    Result result;
    try {
        result.result = States.at(searchString);
        result.isCode = true;
    } catch (const std::out_of_range& e) {
        result.isCode = false;
        result.result = findNameMatch(searchString);
        if (result.result.length() == 0) {
            result.found = false;
        }
    }
    return result;
}

int main(int argc, char const *argv[]) {
    std::ifstream statesFile("states.txt");
    while (!statesFile.eof()) {
        char code[3], name[128];
        statesFile.get(code, 3, '\t');
        statesFile.ignore(1);
        statesFile.get(name, 128);
        States[code] = name;
        statesFile.ignore(1024, '\n');
    }

    char input[1024];
    std::cout << "Sisesta osariigi nimi/kood: ";
    std::cin.getline(input, 1024);

    Result result = getResult(input);
    if (result.found) {
        std::cout << "Osariigi " << (result.isCode ? "nimi" : "kood") << " on: " << result.result;
    } else {
        std::cout << "Vastet ei leitud";
    }
    std::cout << std::endl;
    return 0;
}
