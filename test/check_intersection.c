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

	suite_add_tcase(s, tc_core);
	return s;
}