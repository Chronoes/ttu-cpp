#include "prax2.h"
#include <stdlib.h>

void initialize(SquareMatrix* sm, int dimension) {
    sm->dimension = (unsigned) dimension;
    sm->matrix = new int*[dimension];
}

void assign(SquareMatrix *sm, int *numbers[]) {
    for (size_t i = 0; i < sm->dimension; i++) {
        for (size_t j = 0; j < sm->dimension; j++) {
            sm->matrix[i][j] = numbers[i][j];
        }
    }
}

SquareMatrix mult(SquareMatrix sm1, SquareMatrix sm2) {
}

int main(int argc, char const *argv[]) {
    int numbers[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SquareMatrix sm;
    initialize(&sm, 3);
    assign(&sm, numbers);
    return 0;
}
