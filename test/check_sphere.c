#include <assert.h>
#include <stdlib.h>
#include <check.h>
#include "sphere.h"
#include "tuple.h"
#include "matrix.h"
#include "check_check.h"

START_TEST (sphere_create) {
    Sphere sphere = Sphere_create();
    Tuple expected_origin = Tuple_point(0, 0, 0);
    Matrix expected_transform = Matrix_identity4();

    ck_assert(Tuple_eq(&sphere.origin, &expected_origin));
    ck_assert(Matrix_eq(&sphere.transform, &expected_transform));
}
END_TEST

START_TEST (sphere_set_transformation) {
    Sphere sphere = Sphere_create();
    Tuple expected_origin = Tuple_point(0, 0, 0);
    Matrix expected_transform = Matrix_translation(2, 3, 4);
	Sphere_set_transformation(&sphere, &expected_transform);

    ck_assert(Tuple_eq(&sphere.origin, &expected_origin));
    ck_assert(Matrix_eq(&sphere.transform, &expected_transform));
}
END_TEST

Suite *sphere_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Tuple");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, sphere_create);
	tcase_add_test(tc_core, sphere_set_transformation);

	suite_add_tcase(s, tc_core);
	return s;
}
