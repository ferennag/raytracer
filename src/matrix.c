#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tuple.h"
#include "matrix.h"
#include "util/float.h"

Matrix Matrix_zeroes2() {
    return (Matrix) {
        {
            {0,0},
            {0,0}
        },
        2
    };
}

Matrix Matrix_identity2() {
    return (Matrix) {
        {
            {1,0},
            {0,1}
        },
        2
    };
}


Matrix Matrix_zeroes3() {
    return (Matrix) {
        {
            {0,0,0},
            {0,0,0},
            {0,0,0}
        },
        3
    };
}

Matrix Matrix_identity3() {
    return (Matrix) {
        {
            {1,0,0},
            {0,1,0},
            {0,0,1}
        },
        3
    };
}

Matrix Matrix_zeroes4() {
    return (Matrix) {
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        4
    };
}

Matrix Matrix_identity4() {
    return (Matrix) {
        {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1}
        },
        4
    };
}

Matrix Matrix_create(float *values, unsigned int size) {
    assert(NULL != values && size > 0 && size <= 4);

    Matrix m = Matrix_zeroes4();
    m.size = size;

    for(unsigned int i=0; i < size; ++i) {
        for(unsigned int j=0; j < size; ++j) {
            m.m[i][j] = values[i * size + j];
        }
    }

    return m;
}

void Matrix_print(Matrix *m1) {
    for (int i = 0; i < m1->size; ++i) {
        for (int j = 0; j < m1->size; ++j) {
                printf("%1.2f ", m1->m[i][j]);
        }   
        printf("\n");
    }
}


bool Matrix_eq(Matrix *m1, Matrix *m2) {
    if (NULL == m1 && NULL == m2) {
        return true;
    } else if((NULL == m1 && NULL != m2) || (NULL != m1 && NULL == m2)) {
        return false;
    } else if (m1->size != m2->size) {
        return false;
    } else {
        unsigned short int size = m1->size;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if(!float_eq(m1->m[i][j], m2->m[i][j])) {
                    return false;
                }
            }
        }

        return true;
    }
}

Matrix Matrix_mul(Matrix *m1, Matrix *m2) {
    assert(m1 != NULL && m2 != NULL && m1->size == m2->size);

    Matrix result = Matrix_zeroes4();
    result.size = m1->size;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m1->m[i][k] * m2->m[k][j];
            }
        }
    }

    return result;
}


Tuple Matrix_tmul(const Matrix *m1, const Tuple *t) {
    assert(m1 != NULL && t != NULL);

    float tuple[4] = {0, 0, 0, 0};
    Tuple_as_array(*t, tuple);
    float result[] = {0, 0, 0, 0};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i] += m1->m[i][j] * tuple[j];
        }
    }

    return Tuple_create(result[0], result[1], result[2], result[3]);
}


Matrix Matrix_transpose(Matrix *m1) {
    assert(m1 != NULL);

    Matrix result = Matrix_zeroes4();
    result.size = m1->size;

    for (int i = 0; i < m1->size; ++i) {
        for (int j = 0; j < m1->size; ++j) {
            result.m[j][i] = m1->m[i][j];
        }
    }

    return result;
}

float Matrix_det2(Matrix *m1) {
    assert(m1 != NULL && 2 == m1->size);
    return m1->m[0][0] * m1->m[1][1] - m1->m[0][1] * m1->m[1][0];
}

float Matrix_detN(Matrix *m1) {
    assert(m1 != NULL && m1->size > 2);

    float det = 0;
    for (int i = 0; i < m1->size; ++i) {
        float cofactor = Matrix_cofactor(m1, 0, i);
        float value = m1->m[0][i] * cofactor;
        det += value;
    }

    return det;
}

float Matrix_det(Matrix *m1) {
    assert(NULL != m1);

    if(m1->size == 2) {
        return Matrix_det2(m1);
    } else {
        return Matrix_detN(m1);
    }
}

Matrix Matrix_submatrix(Matrix *m1, unsigned int row, unsigned int col) {
    assert(NULL != m1 && 2 < m1->size && row <= m1->size && col <= m1->size);

    Matrix result = Matrix_zeroes4();
    result.size = m1->size - 1;

    unsigned int srcRow = 0;
    unsigned int srcCol = 0;

    for (int i = 0; i < result.size; ++i) {
        if(srcRow == row) {
            ++srcRow;
        }
        srcCol = 0;
        for (int j = 0; j < result.size; ++j) {
            if(srcCol == col) {
                ++srcCol;
            }
            result.m[i][j] = m1->m[srcRow][srcCol];
            ++srcCol;
        }
        ++srcRow;
    }

    return result;
}

float Matrix_cofactor(Matrix *m1, unsigned int row, unsigned int col) {
    assert(NULL != m1);

    Matrix submatrix = Matrix_submatrix(m1, row, col);
    float minor = Matrix_det(&submatrix);
    if ((row + col) % 2 != 0) {
        return -minor;
    } else {
        return minor;
    }
}

Matrix Matrix_inverse(Matrix *m1) {
    float det = Matrix_det(m1);

    // The determinant is 0. It is non-invertible
    if(abs(det) < 0.00001) {
        // TODO: How to indicate if it's not invertable?
        return *m1;
    } 

    Matrix cofactors = Matrix_zeroes4();
    cofactors.size = m1->size;

    for (int i = 0; i < m1->size; ++i) {
        for (int j = 0; j < m1->size; ++j) {
            float cofactor = Matrix_cofactor(m1, i, j);
            cofactors.m[j][i] = cofactor / det;
        }
    }

    return cofactors;
}

Matrix Matrix_translation(const float x, const float y, const float z) {
    Matrix m = Matrix_identity4();

    m.m[0][3] = x;
    m.m[1][3] = y;
    m.m[2][3] = z;

    return m;
}

Matrix Matrix_scaling(const float x, const float y, const float z) {
    Matrix m = Matrix_identity4();

    m.m[0][0] = x;
    m.m[1][1] = y;
    m.m[2][2] = z;

    return m;
}

Matrix Matrix_rotationX(const float radians) {
    Matrix m = Matrix_identity4();

    m.m[1][1] = cos(radians);
    m.m[1][2] = -sin(radians);
    m.m[2][1] = sin(radians);
    m.m[2][2] = cos(radians);

    return m;
}

Matrix Matrix_rotationY(const float radians) {
    Matrix m = Matrix_identity4();

    m.m[0][0] = cos(radians);
    m.m[0][2] = sin(radians);
    m.m[2][0] = -sin(radians);
    m.m[2][2] = cos(radians);

    return m;
}

Matrix Matrix_rotationZ(const float radians) {
    Matrix m = Matrix_identity4();

    m.m[0][0] = cos(radians);
    m.m[0][1] = -sin(radians);
    m.m[1][0] = sin(radians);
    m.m[1][1] = cos(radians);

    return m;
}

Matrix Matrix_shearing(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy) {
    Matrix m = Matrix_identity4();

    m.m[0][1] = xy;
    m.m[0][2] = xz;
    m.m[1][0] = yx;
    m.m[1][2] = yz;
    m.m[2][0] = zx;
    m.m[2][1] = zy;
    

    return m;
}