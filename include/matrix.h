#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdbool.h>
#include "tuple.h"

#define MAT2(name, ...) \
    float arr_##name[4] = { __VA_ARGS__};\
    Matrix name = Matrix_create(arr_##name,2);

#define MAT3(name, ...) \
    float arr_##name[9] = { __VA_ARGS__};\
    Matrix name = Matrix_create(arr_##name,3);

#define MAT4(name, ...) \
    float arr_##name[16] = { __VA_ARGS__};\
    Matrix name = Matrix_create(arr_##name,4);
    

typedef struct Matrix {
    float m[4][4];
    unsigned short size;
} Matrix;

void Matrix_print(Matrix *m1);

Matrix Matrix_zeroes2();
Matrix Matrix_identity2();

Matrix Matrix_zeroes3();
Matrix Matrix_identity3();

Matrix Matrix_zeroes4();
Matrix Matrix_identity4();

Matrix Matrix_create(float *values, unsigned int size);

bool Matrix_eq(Matrix *m1, Matrix *m2);
Tuple Matrix_tmul(const Matrix *m1, const Tuple *t);
Matrix Matrix_mul(Matrix *m1, Matrix *m2);

Matrix Matrix_transpose(Matrix *m1);

float Matrix_det(Matrix *m1);

Matrix Matrix_submatrix(Matrix *m1, unsigned int row, unsigned int col);
float Matrix_cofactor(Matrix *m1, unsigned int row, unsigned int col);

Matrix Matrix_inverse(Matrix *m1);

Matrix Matrix_translation(const float x, const float y, const float z);
Matrix Matrix_scaling(const float x, const float y, const float z);
Matrix Matrix_rotationX(const float radians);
Matrix Matrix_rotationY(const float radians);
Matrix Matrix_rotationZ(const float radians);
Matrix Matrix_shearing(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy);

#endif