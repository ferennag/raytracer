#include <check.h>
#include <stdlib.h>
#include "check_check.h"
#include "intersection.h"
#include "data/list.h"
#include "util/float.h"

START_TEST (intersection_create) {
    int x = 3333;
    Intersection *i = Intersection_create(10.2, &x);
    ck_assert_float_eq_tol(i->value, 10.2, FLOAT_TOLERANCE);
    ck_assert_ptr_eq(i->object, &x);
    free(i);
}
END_TEST

START_TEST (intersections_create) {
    Intersections *is = Intersections_create();

    ck_assert_int_eq(List_size(is->list), 0);
    ck_assert_int_eq(is->cnt, 0);

    Intersections_destroy(&is);
    ck_assert_ptr_null(is);
}
END_TEST

START_TEST (intersections_add) {
    Intersections *is = Intersections_create();
    Intersections_add(is, 10.2, NULL);

    ck_assert_int_eq(List_size(is->list), 1);
    ck_assert_int_eq(is->cnt, 1);

    Intersections_destroy(&is);
    ck_assert_ptr_null(is);
}
END_TEST

START_TEST (intersections_hit_empty) {
    Intersections *is = Intersections_create();

    Intersection *i = Intersections_hit(is);

    ck_assert_ptr_null(i);

    Intersections_destroy(&is);
    ck_assert_ptr_null(is);
}
END_TEST

START_TEST (intersections_add_auto_sorted) {
    Intersections *is = Intersections_create();
    Intersections_add(is, 5, NULL);
    Intersections_add(is, 7, NULL);
    Intersections_add(is, -3, NULL);
    Intersections_add(is, 2, NULL);
    Intersections_add(is, 11, NULL);

    ck_assert_int_eq(is->cnt, 5);

    Intersection *i1 = Intersections_at(is, 0);
    Intersection *i2 = Intersections_at(is, 1);
    Intersection *i3 = Intersections_at(is, 2);
    Intersection *i4 = Intersections_at(is, 3);
    Intersection *i5 = Intersections_at(is, 4);

    ck_assert_ptr_nonnull(i1);
    ck_assert_ptr_nonnull(i2);
    ck_assert_ptr_nonnull(i3);
    ck_assert_ptr_nonnull(i4);
    ck_assert_ptr_nonnull(i5);

    ck_assert_float_eq_tol(i1->value, -3, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(i2->value, 2, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(i3->value, 5, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(i4->value, 7, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(i5->value, 11, FLOAT_TOLERANCE);

    Intersections_destroy(&is);
    ck_assert_ptr_null(is);
}
END_TEST

START_TEST (intersections_hit_only_negative) {
    Intersections *is = Intersections_create();
    Intersections_add(is, -5, NULL);
    Intersections_add(is, -7, NULL);
    Intersections_add(is, -3, NULL);
    Intersections_add(is, -2, NULL);
    Intersections_add(is, -11, NULL);

    Intersection *i = Intersections_hit(is);

    ck_assert_ptr_null(i);

    Intersections_destroy(&is);
    ck_assert_ptr_null(is);
}
END_TEST

START_TEST (intersections_hit_closest) {
    Intersections *is = Intersections_create();
    Intersections_add(is, 5, NULL);
    Intersections_add(is, 7, NULL);
    Intersections_add(is, -3, NULL);
    Intersections_add(is, 2, NULL);
    Intersections_add(is, 11, NULL);

    Intersection *i = Intersections_hit(is);

    ck_assert_ptr_nonnull(i);
    ck_assert_float_eq_tol(i->value, 2, FLOAT_TOLERANCE);


    Intersections_destroy(&is);
    ck_assert_ptr_null(is);
}
END_TEST

Suite *intersection_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Intersection");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, intersection_create);
	tcase_add_test(tc_core, intersections_create);
	tcase_add_test(tc_core, intersections_add); 
	tcase_add_test(tc_core, intersections_hit_empty); 
	tcase_add_test(tc_core, intersections_hit_only_negative); 
	tcase_add_test(tc_core, intersections_hit_closest); 
	tcase_add_test(tc_core, intersections_add_auto_sorted); 

	suite_add_tcase(s, tc_core);
	return s;
}