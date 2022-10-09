#include <check.h>
#include <math.h>
#include "check_check.h"
#include "matrix.h"
#include "tuple.h"

START_TEST (matrix_create) {
    float values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix result = Matrix_create(values, 3);
    ck_assert_int_eq(result.size, 3);
    ck_assert_float_eq_tol(result.m[0][0], 1, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.m[1][1], 5, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.m[2][2], 9, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (matrix_identity2) {
    Matrix result = Matrix_identity2();
    ck_assert_int_eq(result.size, 2);
    ck_assert_float_eq_tol(result.m[0][0], 1, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.m[1][1], 1, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.m[0][1], 0, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.m[1][0], 0, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (matrix_identity3) {
    Matrix result = Matrix_identity3();
    ck_assert_int_eq(result.size, 3);

    for(int i=0; i < result.size; ++i){
        for(int j=0; j < result.size; ++j){
            const float expected = i == j ? 1 : 0;
            ck_assert_float_eq_tol(result.m[i][j], expected, FLOAT_TOLERANCE);
        }
    }
}
END_TEST

START_TEST (matrix_identity4) {
    Matrix result = Matrix_identity4();
    ck_assert_int_eq(result.size, 4);

    for(int i=0; i < result.size; ++i){
        for(int j=0; j < result.size; ++j){
            const float expected = i == j ? 1 : 0;
            ck_assert_float_eq_tol(result.m[i][j], expected, FLOAT_TOLERANCE);
        }
    }
}
END_TEST

START_TEST (matrix_zeroes2) {
    Matrix result = Matrix_zeroes2();
    ck_assert_int_eq(result.size, 2);

    for(int i=0; i < result.size; ++i){
        for(int j=0; j < result.size; ++j){
            const float expected = 0;
            ck_assert_float_eq_tol(result.m[i][j], expected, FLOAT_TOLERANCE);
        }
    }
}
END_TEST

START_TEST (matrix_zeroes3) {
    Matrix result = Matrix_zeroes3();
    ck_assert_int_eq(result.size, 3);

    for(int i=0; i < result.size; ++i){
        for(int j=0; j < result.size; ++j){
            const float expected = 0;
            ck_assert_float_eq_tol(result.m[i][j], expected, FLOAT_TOLERANCE);
        }
    }
}
END_TEST

START_TEST (matrix_zeroes4) {
    Matrix result = Matrix_zeroes4();
    ck_assert_int_eq(result.size, 4);

    for(int i=0; i < result.size; ++i){
        for(int j=0; j < result.size; ++j){
            const float expected = 0;
            ck_assert_float_eq_tol(result.m[i][j], expected, FLOAT_TOLERANCE);
        }
    }
}
END_TEST

START_TEST (matrix_eq_identical) {
    Matrix m1 = Matrix_identity4();
    Matrix m2 = Matrix_identity4();
    ck_assert(Matrix_eq(&m1, &m2));
}
END_TEST

START_TEST (matrix_eq_not_identical) {
    Matrix m1 = Matrix_identity4();
    Matrix m2 = Matrix_identity4();
    m2.m[0][0] = 4;
    ck_assert(!Matrix_eq(&m1, &m2));
}
END_TEST

START_TEST (matrix_eq_identical_different_size) {
    Matrix m1 = Matrix_identity4();
    Matrix m2 = Matrix_identity3();
    ck_assert(!Matrix_eq(&m1, &m2));
}
END_TEST

START_TEST (matrix_mul) {
    MAT4(m1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
    MAT4(m2, -2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8);
    MAT4(expected, 20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42);

    Matrix result = Matrix_mul(&m1, &m2);
    ck_assert(Matrix_eq(&result, &expected));
}
END_TEST

START_TEST (matrix_mul_tuple) {
    MAT4(m1, 1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1);
    Tuple t1 = Tuple_create(1, 2, 3, 1);
    Tuple expected = Tuple_create(18, 24, 33, 1);

    Tuple result = Matrix_tmul(&m1, &t1);
    ck_assert(Tuple_eq(&result, &expected));
}
END_TEST

START_TEST (matrix_transpose_identity) {
    Matrix m1 = Matrix_identity4();
    Matrix expected = Matrix_identity4();
    Matrix result = Matrix_transpose(&m1);

    ck_assert(Matrix_eq(&result, &expected));
}
END_TEST

START_TEST (matrix_transpose) {
    MAT4(m1, 0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8);
    MAT4(expected, 0,9,1,0,  9,8,8,0,  3,0,5,5,  0,8,3,8);
    Matrix result = Matrix_transpose(&m1);

    ck_assert(Matrix_eq(&result, &expected));
}
END_TEST

START_TEST (matrix_det2) {
    MAT2(m1, 1, 5, -3, 2);
    float result = Matrix_det(&m1);

    ck_assert_float_eq_tol(result, 17, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (matrix_submatrix) {
    MAT3(m1, 1, 5, 0, -3, 2, 7, 0, 6, -3);
    MAT2(expected, -3, 2, 0, 6);
    Matrix result = Matrix_submatrix(&m1, 0, 2);

    ck_assert(Matrix_eq(&result, &expected));
}
END_TEST

START_TEST (matrix_det3) {
    MAT3(m1, 1, 2, 6, -5, 8, -4, 2, 6, 4);
    float result = Matrix_det(&m1);

    ck_assert_float_eq_tol(result, -196, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (matrix_det4) {
    MAT4(m1, -2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9);
    float result = Matrix_det(&m1);

    ck_assert_float_eq_tol(result, -4071, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (matrix_inverse) {
    MAT4(m1, -5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4);
    MAT4(expected, 0.2180, 0.4511, 0.2406, -0.0451, -0.8082, -1.4567, -0.4436, 0.5206, -0.0789, -0.2236, -0.0526, 0.1973, -0.5225, -0.8139, -0.3007, 0.3063);
    Matrix result = Matrix_inverse(&m1);

    ck_assert(Matrix_eq(&result, &expected));
}
END_TEST

START_TEST (matrix_inverse_mul) {
    MAT3(m1, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    MAT3(m2, -2, -2, 1, 3, 2, 2, 3, 3, -9);
    Matrix tmp = Matrix_mul(&m1, &m2);
    Matrix inverseM2 = Matrix_inverse(&m2);
    Matrix result = Matrix_mul(&tmp, &inverseM2);

    ck_assert(Matrix_eq(&result, &m1));
}
END_TEST

START_TEST (matrix_translation) {
    Matrix m1 = Matrix_translation(1, 2, 3);
    MAT4(expected, 1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1)

    ck_assert(Matrix_eq(&m1, &expected));
}
END_TEST

START_TEST (matrix_scaling) {
    Matrix m1 = Matrix_scaling(1, 2, 3);
    MAT4(expected, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1)

    ck_assert(Matrix_eq(&m1, &expected));
}
END_TEST

START_TEST (matrix_rotationX) {
    const float rad = 45;
    Matrix m1 = Matrix_rotationX(rad);
    MAT4(expected, 1, 0, 0, 0, 0, cosf(rad), -sinf(rad), 0, 0, sinf(rad), cosf(rad), 0, 0, 0, 0, 1)

    ck_assert(Matrix_eq(&m1, &expected));
}
END_TEST

START_TEST (matrix_rotationY) {
    const float rad = 45;
    Matrix m1 = Matrix_rotationY(rad);
    MAT4(expected, cosf(rad), 0, sinf(rad), 0, 0, 1, 0, 0, -sinf(rad), 0, cosf(rad), 0, 0, 0, 0, 1)

    ck_assert(Matrix_eq(&m1, &expected));
}
END_TEST

START_TEST (matrix_rotationZ) {
    const float rad = 45;
    Matrix m1 = Matrix_rotationZ(rad);
    MAT4(expected, cosf(rad), -sinf(rad), 0, 0, sinf(rad), cosf(rad), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)

    ck_assert(Matrix_eq(&m1, &expected));
}
END_TEST

START_TEST (matrix_shearing) {
    Matrix m1 = Matrix_shearing(1, 2, 3, 4, 5, 6);
    MAT4(expected, 1, 1, 2, 0, 3, 1, 4, 0, 5, 6, 1, 0, 0, 0, 0, 1)

    ck_assert(Matrix_eq(&m1, &expected));
}
END_TEST

Suite *matrix_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Matrix");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, matrix_create);
	tcase_add_test(tc_core, matrix_identity2);
	tcase_add_test(tc_core, matrix_identity3);
	tcase_add_test(tc_core, matrix_identity4);
	tcase_add_test(tc_core, matrix_zeroes2);
	tcase_add_test(tc_core, matrix_zeroes3);
	tcase_add_test(tc_core, matrix_zeroes4);
	tcase_add_test(tc_core, matrix_eq_identical);
	tcase_add_test(tc_core, matrix_eq_not_identical);
	tcase_add_test(tc_core, matrix_eq_identical_different_size);
	tcase_add_test(tc_core, matrix_mul);
	tcase_add_test(tc_core, matrix_mul_tuple);
	tcase_add_test(tc_core, matrix_transpose_identity);
	tcase_add_test(tc_core, matrix_transpose);
	tcase_add_test(tc_core, matrix_det2);
	tcase_add_test(tc_core, matrix_submatrix);
	tcase_add_test(tc_core, matrix_det3);
	tcase_add_test(tc_core, matrix_det4);
	tcase_add_test(tc_core, matrix_inverse);
	tcase_add_test(tc_core, matrix_inverse_mul);
	tcase_add_test(tc_core, matrix_translation);
	tcase_add_test(tc_core, matrix_scaling);
	tcase_add_test(tc_core, matrix_rotationX);
	tcase_add_test(tc_core, matrix_rotationY);
	tcase_add_test(tc_core, matrix_rotationZ);
	tcase_add_test(tc_core, matrix_shearing);

	suite_add_tcase(s, tc_core);
	return s;
}