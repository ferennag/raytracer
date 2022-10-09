#include <check.h>
#include "tuple.h"
#include "check_check.h"

START_TEST (tuple_point) {
    Tuple point = Tuple_point(1.0, 2.0, 3.0);
    ck_assert_float_eq(point.x, 1.0);
    ck_assert_float_eq(point.y, 2.0);
    ck_assert_float_eq(point.z, 3.0);
	ck_assert_float_eq(point.w, 1.0);
}
END_TEST

START_TEST (tuple_vector) {
    Tuple vector = Tuple_vector(1.0, 2.0, 3.0);
    ck_assert_float_eq(vector.x, 1.0);
    ck_assert_float_eq(vector.y, 2.0);
    ck_assert_float_eq(vector.z, 3.0);
	ck_assert_float_eq(vector.w, 0.0);
}
END_TEST

START_TEST (tuple_add_vector) {
    Tuple t1 = Tuple_vector(3, -2, 5);
	Tuple t2 = Tuple_vector(-2, 3, 1);
	Tuple result = Tuple_add(t1, t2);
    ck_assert_float_eq(result.x, 1.0);
    ck_assert_float_eq(result.y, 1.0);
    ck_assert_float_eq(result.z, 6.0);
	ck_assert_float_eq(result.w, 0.0);
}
END_TEST

START_TEST (tuple_add_points) {
    Tuple t1 = Tuple_point(3, -2, 5);
	Tuple t2 = Tuple_point(-2, 3, 1);
	Tuple result = Tuple_add(t1, t2);
    ck_assert_float_eq(result.x, 1.0);
    ck_assert_float_eq(result.y, 1.0);
    ck_assert_float_eq(result.z, 6.0);
	ck_assert_float_eq(result.w, 2.0);
}
END_TEST

START_TEST (tuple_sub_points) {
    Tuple t1 = Tuple_point(3, -2, 5);
	Tuple t2 = Tuple_point(-2, 3, 1);
	Tuple result = Tuple_sub(t1, t2);
    ck_assert_float_eq(result.x,  5);
    ck_assert_float_eq(result.y, -5);
    ck_assert_float_eq(result.z,  4);
	ck_assert_float_eq(result.w,  0);
}
END_TEST

START_TEST (tuple_sub_vectors) {
    Tuple t1 = Tuple_vector(3, -2, 5);
	Tuple t2 = Tuple_vector(-2, 3, 1);
	Tuple result = Tuple_sub(t1, t2);
    ck_assert_float_eq(result.x,  5);
    ck_assert_float_eq(result.y, -5);
    ck_assert_float_eq(result.z,  4);
	ck_assert_float_eq(result.w,  0);
}
END_TEST

START_TEST (tuple_negate) {
    Tuple t1 = Tuple_point(3, -2, 5);
	Tuple result = Tuple_negate(t1);
    ck_assert_float_eq(result.x, -3);
    ck_assert_float_eq(result.y,  2);
    ck_assert_float_eq(result.z, -5);
	ck_assert_float_eq(result.w, -1);
}
END_TEST

START_TEST (tuple_mul_by_scalar) {
    Tuple t1 = Tuple_point(3, -2, 5);
	Tuple result = Tuple_smul(t1, 0.5f);
    ck_assert_float_eq(result.x, 1.5);
    ck_assert_float_eq(result.y,  -1);
    ck_assert_float_eq(result.z, 2.5);
	ck_assert_float_eq(result.w, 0.5);
}
END_TEST

START_TEST (tuple_div_by_scalar) {
    Tuple t1 = Tuple_point(3, -2, 5);
	Tuple result = Tuple_sdiv(t1, 2.0f);
    ck_assert_float_eq(result.x, 1.5);
    ck_assert_float_eq(result.y,  -1);
    ck_assert_float_eq(result.z, 2.5);
	ck_assert_float_eq(result.w, 0.5);
}
END_TEST

START_TEST (tuple_magnitude1) {
    Tuple t1 = Tuple_vector(1, 0, 0);
	float result = Tuple_magnitude(t1);
    ck_assert_float_eq(result, 1.0);
}
END_TEST

START_TEST (tuple_magnitude2) {
    Tuple t1 = Tuple_vector(0, 1, 0);
	float result = Tuple_magnitude(t1);
    ck_assert_float_eq(result, 1.0);
}
END_TEST

START_TEST (tuple_magnitude3) {
    Tuple t1 = Tuple_vector(1, 2, 3);
	float result = Tuple_magnitude(t1);
    ck_assert_float_eq(result, sqrt(14));
}
END_TEST

START_TEST (tuple_magnitude4) {
    Tuple t1 = Tuple_vector(-1, -2, -3);
	float result = Tuple_magnitude(t1);
    ck_assert_float_eq(result, sqrt(14));
}
END_TEST

START_TEST (tuple_normalize1) {
    Tuple t1 = Tuple_vector(4, 0, 0);
	Tuple result = Tuple_normalize(t1);
   	ck_assert_float_eq(result.x, 1);
    ck_assert_float_eq(result.y, 0);
    ck_assert_float_eq(result.z, 0);
	ck_assert_float_eq(result.w, 0);
}
END_TEST

START_TEST (tuple_normalize2) {
    Tuple t1 = Tuple_vector(1, 2, 3);
	Tuple result = Tuple_normalize(t1);
   	ck_assert_float_eq_tol(result.x, 0.267, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.y, 0.534, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.z, 0.801, FLOAT_TOLERANCE);
	ck_assert_float_eq_tol(result.w, 0, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (tuple_dot) {
    Tuple t1 = Tuple_vector(1, 2, 3);
	Tuple t2 = Tuple_vector(2, 3, 4);
	float result = Tuple_dot(t1, t2);
   	ck_assert_float_eq_tol(result, 20, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (tuple_cross1) {
    Tuple t1 = Tuple_vector(1, 2, 3);
	Tuple t2 = Tuple_vector(2, 3, 4);
	Tuple result = Tuple_cross(t1, t2);
   	ck_assert_float_eq_tol(result.x, -1, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.y, 2, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.z, -1, FLOAT_TOLERANCE);
	ck_assert_float_eq_tol(result.w, 0, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (tuple_cross2) {
    Tuple t1 = Tuple_vector(1, 2, 3);
	Tuple t2 = Tuple_vector(2, 3, 4);
	Tuple result = Tuple_cross(t2, t1);
   	ck_assert_float_eq_tol(result.x, 1, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.y, -2, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.z, 1, FLOAT_TOLERANCE);
	ck_assert_float_eq_tol(result.w, 0, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (tuple_create_color) {
    Tuple t1 = Tuple_color(1, 2, 3);
   	ck_assert_float_eq_tol(t1.x, 1, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(t1.y, 2, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(t1.z, 3, FLOAT_TOLERANCE);
	ck_assert_float_eq_tol(t1.w, 0, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (tuple_hadamard) {
    Tuple t1 = Tuple_color(1, 0.2, 0.4);
    Tuple t2 = Tuple_color(0.9, 1, 0.1);
    Tuple result = Tuple_hadamard(t1, t2);
   	ck_assert_float_eq_tol(result.x, 0.9, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.y, 0.2, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(result.z, 0.04, FLOAT_TOLERANCE);
	ck_assert_float_eq_tol(result.w, 0, FLOAT_TOLERANCE);
}
END_TEST

Suite *tuple_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Tuple");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, tuple_point);
	tcase_add_test(tc_core, tuple_vector);
	tcase_add_test(tc_core, tuple_add_vector);
	tcase_add_test(tc_core, tuple_add_points);
	tcase_add_test(tc_core, tuple_sub_points);
	tcase_add_test(tc_core, tuple_sub_vectors);
	tcase_add_test(tc_core, tuple_negate);
	tcase_add_test(tc_core, tuple_mul_by_scalar);
	tcase_add_test(tc_core, tuple_div_by_scalar);
	tcase_add_test(tc_core, tuple_magnitude1);
	tcase_add_test(tc_core, tuple_magnitude2);
	tcase_add_test(tc_core, tuple_magnitude3);
	tcase_add_test(tc_core, tuple_magnitude4);
	tcase_add_test(tc_core, tuple_normalize1);
	tcase_add_test(tc_core, tuple_normalize2);
	tcase_add_test(tc_core, tuple_dot);
	tcase_add_test(tc_core, tuple_cross1);
	tcase_add_test(tc_core, tuple_cross2);
	tcase_add_test(tc_core, tuple_create_color);
	tcase_add_test(tc_core, tuple_hadamard);

	suite_add_tcase(s, tc_core);
	return s;
}

