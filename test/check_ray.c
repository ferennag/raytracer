#include <check.h>
#include <stdio.h>
#include "check_check.h"
#include "ray.h"
#include "tuple.h"
#include "matrix.h"
#include "sphere.h"
#include "util/float.h"

START_TEST (ray_create) {
    Tuple origin = Tuple_point(1, 2, 3);
    Tuple direction = Tuple_vector(1, 2, 3);

    Ray ray = Ray_create(origin, direction);
    ck_assert(Tuple_eq(&ray.origin, &origin));
    ck_assert(Tuple_eq(&ray.direction, &direction));
}
END_TEST

START_TEST (ray_position) {
    Tuple origin = Tuple_point(2, 3, 4);
    Tuple direction = Tuple_vector(1, 0, 0);
    Ray ray = Ray_create(origin, direction);

    Tuple t0 = Ray_position(&ray, 0);
    Tuple t0_expected = Tuple_point(2, 3, 4);

    Tuple t1 = Ray_position(&ray, 1);
    Tuple t1_expected = Tuple_point(3, 3, 4);

    Tuple t2 = Ray_position(&ray, -1);
    Tuple t2_expected = Tuple_point(1, 3, 4);

    Tuple t3 = Ray_position(&ray, 2.5);
    Tuple t3_expected = Tuple_point(4.5, 3, 4);
    
    ck_assert(Tuple_eq(&t0, &t0_expected));
    ck_assert(Tuple_eq(&t1, &t1_expected));
    ck_assert(Tuple_eq(&t2, &t2_expected));
    ck_assert(Tuple_eq(&t3, &t3_expected));
}
END_TEST

START_TEST (ray_intersect_sphere_cross) {
    Tuple origin = Tuple_point(0, 0, -5);
    Tuple direction = Tuple_vector(0, 0, 1);
    Ray ray = Ray_create(origin, direction);
    Sphere sphere = Sphere_create();

    Intersections *intersected = Ray_intersect(&ray, &sphere);
    ck_assert_int_eq(intersected->cnt, 2);
    ck_assert_int_eq(List_size(intersected->list), 2);

    Intersection *first = (Intersection *)intersected->list->head->next->data;
    Intersection *second = (Intersection *)intersected->list->head->next->next->data;

    ck_assert_float_eq_tol(first->value, 4.0, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(second->value, 6.0, FLOAT_TOLERANCE);
    ck_assert_ptr_eq(first->object, &sphere);
    ck_assert_ptr_eq(second->object, &sphere);
    Intersections_destroy(&intersected);
}
END_TEST

START_TEST (ray_intersect_scaled_sphere) {
    Ray ray = Ray_create(Tuple_point(0, 0, -5), Tuple_vector(0, 0, 1));
    Sphere sphere = Sphere_create();
    Matrix scaling = Matrix_scaling(2, 2, 2);
    Sphere_set_transformation(&sphere, &scaling);

    Intersections *intersected = Ray_intersect(&ray, &sphere);
    ck_assert_int_eq(intersected->cnt, 2);

    Intersection *first = (Intersection *)List_first(intersected->list)->data;
    Intersection *second = (Intersection *)List_last(intersected->list)->data;

    ck_assert_float_eq_tol(first->value, 3.0, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(second->value, 7.0, FLOAT_TOLERANCE);
    ck_assert_ptr_eq(first->object, &sphere);
    ck_assert_ptr_eq(second->object, &sphere);
    Intersections_destroy(&intersected);
}
END_TEST


START_TEST (ray_intersect_translated_sphere) {
    Ray ray = Ray_create(Tuple_point(0, 0, -5), Tuple_vector(0, 0, 1));
    Sphere sphere = Sphere_create();
    Matrix scaling = Matrix_translation(5, 0, 0);
    Sphere_set_transformation(&sphere, &scaling);

    Intersections *intersected = Ray_intersect(&ray, &sphere);
    ck_assert_int_eq(intersected->cnt, 0);
    Intersections_destroy(&intersected);
}
END_TEST

START_TEST (ray_intersect_sphere_tangent) {
    Tuple origin = Tuple_point(0, 1, -5);
    Tuple direction = Tuple_vector(0, 0, 1);
    Ray ray = Ray_create(origin, direction);
    Sphere sphere = Sphere_create();

    Intersections *intersected = Ray_intersect(&ray, &sphere);
    ck_assert_int_eq(intersected->cnt, 2);
    Intersection *first = (Intersection *)intersected->list->head->next->data;
    Intersection *second = (Intersection *)intersected->list->head->next->next->data;

    ck_assert_float_eq_tol(first->value, 5.0, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(second->value, 5.0, FLOAT_TOLERANCE);
    ck_assert_ptr_eq(first->object, &sphere);
    ck_assert_ptr_eq(second->object, &sphere);
    Intersections_destroy(&intersected);
}
END_TEST

START_TEST (ray_miss_sphere) {
    Tuple origin = Tuple_point(0, 2, -5);
    Tuple direction = Tuple_vector(0, 0, 1);
    Ray ray = Ray_create(origin, direction);
    Sphere sphere = Sphere_create();

    Intersections *intersected = Ray_intersect(&ray, &sphere);
    ck_assert_int_eq(intersected->cnt, 0);
    Intersections_destroy(&intersected);
}
END_TEST

START_TEST (ray_intersect_from_center_of_sphere) {
    Tuple origin = Tuple_point(0, 0, 0);
    Tuple direction = Tuple_vector(0, 0, 1);
    Ray ray = Ray_create(origin, direction);
    Sphere sphere = Sphere_create();

    Intersections *intersected = Ray_intersect(&ray, &sphere);
    ck_assert_int_eq(intersected->cnt, 2);
    Intersection *first = (Intersection *)intersected->list->head->next->data;
    Intersection *second = (Intersection *)intersected->list->head->next->next->data;

    ck_assert_float_eq_tol(first->value, -1.0, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(second->value, 1.0, FLOAT_TOLERANCE);
    ck_assert_ptr_eq(first->object, &sphere);
    ck_assert_ptr_eq(second->object, &sphere);
    Intersections_destroy(&intersected);
}
END_TEST

START_TEST (ray_intersect_from_behind_of_sphere) {
    Tuple origin = Tuple_point(0, 0, 5);
    Tuple direction = Tuple_vector(0, 0, 1);
    Ray ray = Ray_create(origin, direction);
    Sphere sphere = Sphere_create();

    Intersections *intersected = Ray_intersect(&ray, &sphere);
    ck_assert_int_eq(intersected->cnt, 2);
    Intersection *first = (Intersection *)intersected->list->head->next->data;
    Intersection *second = (Intersection *)intersected->list->head->next->next->data;

    ck_assert_float_eq_tol(first->value, -6.0, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(second->value, -4.0, FLOAT_TOLERANCE);
    ck_assert_ptr_eq(first->object, &sphere);

    Intersections_destroy(&intersected);
}
END_TEST

START_TEST (ray_transform_translation) {
    Tuple origin = Tuple_point(1, 2, 3);
    Tuple direction = Tuple_vector(0, 1, 0);
    Ray ray = Ray_create(origin, direction);
    Matrix translation = Matrix_translation(3, 4 ,5);
    Ray result = Ray_transform(&ray, &translation);

    Tuple expected_origin = Tuple_point(4, 6, 8);
    Tuple expected_direction = Tuple_vector(0, 1, 0);


    ck_assert(Tuple_eq(&expected_origin, &result.origin));
    ck_assert(Tuple_eq(&expected_direction, &result.direction));
}
END_TEST

START_TEST (ray_transform_scaling) {
    Tuple origin = Tuple_point(1, 2, 3);
    Tuple direction = Tuple_vector(0, 1, 0);
    Ray ray = Ray_create(origin, direction);
    Matrix translation = Matrix_scaling(2, 3, 4);
    Ray result = Ray_transform(&ray, &translation);

    Tuple expected_origin = Tuple_point(2, 6, 12);
    Tuple expected_direction = Tuple_vector(0, 3, 0);


    ck_assert_mem_eq(&expected_origin, &result.origin, sizeof(Tuple));
    ck_assert_mem_eq(&expected_direction, &result.direction, sizeof(Tuple));
}
END_TEST

Suite *ray_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Ray");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, ray_create);
	tcase_add_test(tc_core, ray_position);
	tcase_add_test(tc_core, ray_intersect_sphere_cross);
	tcase_add_test(tc_core, ray_intersect_scaled_sphere);
	tcase_add_test(tc_core, ray_intersect_translated_sphere);
	tcase_add_test(tc_core, ray_intersect_sphere_tangent);
	tcase_add_test(tc_core, ray_miss_sphere);
	tcase_add_test(tc_core, ray_intersect_from_center_of_sphere);
	tcase_add_test(tc_core, ray_intersect_from_behind_of_sphere);
	tcase_add_test(tc_core, ray_transform_translation);
	tcase_add_test(tc_core, ray_transform_scaling);

	suite_add_tcase(s, tc_core);
	return s;
}
