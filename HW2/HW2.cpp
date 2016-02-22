#include <iostream>
#include <cmath>
#include <stdio.h>
#include "HW2.h"

#define MAX_TRIALS 5
#define MAX_OPERATIONS 100000000

double pi(unsigned precision) {
    double sum = 0;
    unsigned i = 0;
    precision++;
    while (fabs(M_PI - sum) > pow(0.1, precision) && i < MAX_OPERATIONS) {
        sum += (i % 2 == 0 ? 1 : -1) * (4.0 / (2 * i + 1));
        i++;
    }
    return sum;
}

int guessTheNumber(unsigned number) {
    unsigned lower = 0, upper = 100, trial, maxTrials = MAX_TRIALS;

    while (maxTrials--) {
        std::cout << "Input a number: ";
        std::cin >> trial;
        std::cout << std::endl;
        switch (arbiter(lower, upper, trial, number)) {
            case GUESS:
                std::cout << "You guessed it!" << std::endl;
                return 0;
            case LEFT:
                std::cout << "The number is lower." << std::endl;
                upper = trial;
                break;
            case RIGHT:
                std::cout << "The number is higher." << std::endl;
                lower = trial;
                break;
            case ERROR:
                std::cout << "The guessed number is out of bounds." << std::endl;
                return 1;
            default:
                break;
        }
    }
    std::cout << "Maximum trials exceeded." << std::endl;
    return 1;
}

Result arbiter(unsigned lower, unsigned upper, unsigned trial, unsigned number) {
    if (trial == number) {
        return GUESS;
    } else if (number < trial && trial < upper) {
        return LEFT;
    } else if (lower < trial && trial < number) {
        return RIGHT;
    } else {
        return ERROR;
    }
}

int main(int argc, char const *argv[]) {
    printf("%.8f\n", pi(8));
    guessTheNumber(50);
    return 0;
}
