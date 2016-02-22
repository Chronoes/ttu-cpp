#ifndef HW2_H_INCLUDED
#define HW2_H_INCLUDED

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

using namespace std;

void count2zero(auto start, auto step) {

    for(auto i = start; i >= step; i -= step){
        cout << i << " ";
    }

    cout << endl << endl;
}

string typeName(auto i) {

    int status = 0;
    return string(abi::__cxa_demangle(typeid(i).name(), 0, 0, &status));
}

double pi(unsigned precision);

typedef enum Result {
    ERROR = -1,
    GUESS,
    RIGHT,
    LEFT
} Result;

int guessTheNumber(unsigned);
Result arbiter(unsigned, unsigned, unsigned, unsigned);

#endif // HW2_H_INCLUDED
