#ifndef SQUAREMATRIX_H_INCLUDED
#define SQUAREMATRIX_H_INCLUDED

typedef struct SquareMatrix_t {
    int** matrix;
    unsigned dimension;
} SquareMatrix;

//Allocates memory for 3x3 matrix and copies values from array2D
void initialize(SquareMatrix* sm, int dimension);
void assign(SquareMatrix *sm, int *numbers[]);
//Matrix multiplication. Returns the product of sm1 and sm2.
SquareMatrix mult(SquareMatrix sm1, SquareMatrix sm2);
//Reallocates the memory allocated dinamically with initialize().
void deleteMatrix(SquareMatrix* sm);

#endif // SQUAREMATRIX_H_INCLUDED
