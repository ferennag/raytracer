#include <check.h>
#include "check_check.h"

int main(void)
{
	SRunner *sr = srunner_create(tuple_suite());
	srunner_add_suite(sr, matrix_suite());
	srunner_add_suite(sr, float_suite());
	srunner_add_suite(sr, ray_suite());
	srunner_add_suite(sr, intersection_suite());

	srunner_run_all(sr, CK_NORMAL);
	int failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return failed;
}