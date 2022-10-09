#include <check.h>
#include <stdbool.h>
#include "check_check.h"
#include "util/float.h"

START_TEST (float_test_eq) {
    float a = 0.1;
    float b = 0.1;
    ck_assert(float_eq(a, b));
}
END_TEST

START_TEST (float_test_eq2) {
    float a = 0.0001;
    float b = 0.0002;
    ck_assert(float_eq(a, b));
}
END_TEST

START_TEST (float_test_eq3) {
    float a = 0.1001;
    float b = 0.1002;
    ck_assert(float_eq(a, b));
}
END_TEST

START_TEST (float_test_neq) {
    float a = 0.1;
    float b = 0.2;
    ck_assert(!float_eq(a, b));
}
END_TEST

Suite *float_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Utils/Float");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, float_test_eq);
	tcase_add_test(tc_core, float_test_eq2);
	tcase_add_test(tc_core, float_test_eq3);
	tcase_add_test(tc_core, float_test_neq);

	suite_add_tcase(s, tc_core);
	return s;
}