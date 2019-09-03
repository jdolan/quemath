/*
 * Quemath: An SSE optimized 3D math library for games.
 * Copyright (C) 2019 Jay Dolan <jay@jaydolan.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <check.h>
#include <stdio.h>

#include "vec.h"

static inline void assert_flt_eq(float a, float b, float epsilon) {
	ck_assert_msg(fabsf(a - b) < epsilon, "%g != %g", a, b);
}

static inline void assert_vec_eq(const vec a, const vec b) {
	ck_assert_msg(vec_equals(a, b), "(%g, %g, %g, %g) == (%g, %g, %g, %g)",
				  vec_x(a), vec_y(a), vec_z(a), vec_w(a),
				  vec_x(b), vec_y(b), vec_z(b), vec_w(b));
}

START_TEST(_vec0) {
	assert_vec_eq(vec4(0, 0, 0, 0), vec0());
} END_TEST

START_TEST(_vec1) {
	assert_vec_eq(vec4(1, 0, 0, 0), vec1(1));
} END_TEST

START_TEST(_vec2) {
	assert_vec_eq(vec4(1, 2, 0, 0), vec2(1, 2));
} END_TEST

START_TEST(_vec3) {
	assert_vec_eq(vec4(1, 2, 3, 0), vec3(1, 2, 3));
} END_TEST

START_TEST(_vec4) {
	assert_vec_eq(vec4(1, 2, 3, 4), vec4(1, 2, 3, 4));
} END_TEST

START_TEST(_vec_add) {
	assert_vec_eq(vec_add(vec3(1, 2, 3), vec3(1, 1, 1)), vec3(2, 3, 4));
} END_TEST

START_TEST(_vec_cross) {
	assert_vec_eq(vec3(-3, 6, -3), vec_cross(vec3(1, 2, 3), vec3(4, 5, 6)));
} END_TEST

START_TEST(_vec_degrees) {
	assert_vec_eq(vec1(180), vec_degrees(vec1(M_PI)));
} END_TEST

START_TEST(_vec_distance) {
	assert_vec_eq(vec1(5), vec_distance(vec2(0, 0), vec2(3, 4)));
} END_TEST

START_TEST(_vec_divide) {
	assert_vec_eq(vec3(1, 2, 3), vec_divide(vec3(1, 4, 9), vec4(1, 2, 3, 1)));
} END_TEST

START_TEST(_vec_dot) {
	assert_vec_eq(vec1( 1), vec_dot(vec3(1, 0, 0), vec3( 1, 0, 0)));
	assert_vec_eq(vec1(-1), vec_dot(vec3(1, 0, 0), vec3(-1, 0, 0)));
	assert_vec_eq(vec1( 0), vec_dot(vec3(1, 0, 0), vec3( 0, 1, 0)));
} END_TEST

START_TEST(_vec_equal) {
	ck_assert_int_eq(1, vec_equals(vec_new(1), vec_new(1)));
	ck_assert_int_eq(1, vec_equals(vec3(1, 2, 3), vec3(1, 2, 3)));
	ck_assert_int_eq(0, vec_equals(vec_new(1), vec_new(2)));
} END_TEST

START_TEST(_vec_greater_than) {
	ck_assert_int_eq(1, vec_greater_than(vec_new(1), vec_new(0)));
	ck_assert_int_eq(0, vec_greater_than(vec_new(0), vec_new(1)));
	ck_assert_int_eq(0, vec_greater_than(vec_new(0), vec_new(0)));
} END_TEST

START_TEST(_vec_greater_than_equal) {
	ck_assert_int_eq(1, vec_greater_than_equal(vec_new(1), vec_new(0)));
	ck_assert_int_eq(0, vec_greater_than_equal(vec_new(0), vec_new(1)));
	ck_assert_int_eq(1, vec_greater_than_equal(vec_new(0), vec_new(0)));
} END_TEST

START_TEST(_vec_length) {
	assert_vec_eq(vec1(1), vec_length(vec3(1, 0, 0)));
	assert_vec_eq(vec1(2), vec_length(vec3(2, 0, 0)));
	assert_vec_eq(vec1(5), vec_length(vec3(3, 0, 4)));
} END_TEST

START_TEST(_vec_less_than) {
	ck_assert_int_eq(1, vec_less_than(vec_new(0), vec_new(1)));
	ck_assert_int_eq(0, vec_less_than(vec_new(1), vec_new(0)));
	ck_assert_int_eq(0, vec_less_than(vec_new(0), vec_new(0)));
} END_TEST

START_TEST(_vec_less_than_equal) {
	ck_assert_int_eq(1, vec_less_than_equal(vec_new(0), vec_new(1)));
	ck_assert_int_eq(0, vec_less_than_equal(vec_new(1), vec_new(0)));
	ck_assert_int_eq(1, vec_less_than_equal(vec_new(0), vec_new(0)));
} END_TEST

START_TEST(_vec_mix) {
	assert_vec_eq(vec_new(0), vec_mix(vec_new(0), vec_new(1), 0));
	assert_vec_eq(vec_new(1), vec_mix(vec_new(0), vec_new(1), 1));
	assert_vec_eq(vec_new(1), vec_mix(vec_new(0), vec_new(2), 0.5));
} END_TEST

START_TEST(_vec_multiply) {
	assert_vec_eq(vec3(4, 10, 18), vec_multiply(vec3(1, 2, 3), vec3(4, 5, 6)));
} END_TEST

START_TEST(_vec_negate) {
	assert_vec_eq(vec3(-1, -2, -3), vec_negate(vec3(1, 2, 3)));
} END_TEST

START_TEST(_vec_normalize) {
	assert_vec_eq(vec1(1), vec_normalize(vec3(1, 0, 0)));
	assert_vec_eq(vec1(1), vec_normalize(vec3(2, 0, 0)));
	assert_vec_eq(vec3(1 / sqrtf(3), 1 / sqrtf(3), 1 / sqrtf(3)), vec_normalize(vec3(1, 1, 1)));
} END_TEST

START_TEST(_vec_normalize_fast) {
	assert_flt_eq(1, vec_x(vec_length(vec_normalize_fast(vec3(1, 0, 0)))), 0.001);
	assert_flt_eq(1, vec_x(vec_length(vec_normalize_fast(vec3(2, 0, 0)))), 0.001);
	assert_flt_eq(1, vec_x(vec_length(vec_normalize_fast(vec3(1, 2, 3)))), 0.001);
	assert_flt_eq(1, vec_x(vec_length(vec_normalize_fast(vec3(2, 0, 2)))), 0.001);
} END_TEST

START_TEST(_vec_not_equal) {
	ck_assert_int_eq(1, vec_not_equal(vec_new(0), vec_new(1)));
	ck_assert_int_eq(0, vec_not_equal(vec_new(1), vec_new(1)));
} END_TEST

START_TEST(_vec_radians) {
	assert_vec_eq(vec0(), vec_radians(vec0()));
	assert_vec_eq(vec1(M_PI), vec_radians(vec1(180)));
	assert_vec_eq(vec1(M_PI / 2), vec_radians(vec1(90)));
} END_TEST

START_TEST(_vec_random) {
	vec rand = vec4(0xfeed, 0xdad, 0xdead, 0xbeef);

	const int iterations = 1000;
	for (int i = 0; i < iterations; i++) {
		rand = vec_random(rand);
		ck_assert_int_eq(1, vec_greater_than_equal(rand, vec_new(0)));
		ck_assert_int_eq(1, vec_less_than(rand, vec_new(1)));
	}
} END_TEST

START_TEST(_vec_random_range) {
	vec rand = vec4(0xfeed, 0xdad, 0xdead, 0xbeef);

	const int iterations = 1000;
	for (int i = 0; i < iterations; i++) {
		rand = vec_random_range(rand, vec_new(i), vec_new(iterations));
		ck_assert_int_eq(1, vec_greater_than_equal(rand, vec_new(i)));
		ck_assert_int_eq(1, vec_less_than(rand, vec_new(iterations)));
	}
} END_TEST

START_TEST(_vec_rsqrt) {
	const vec v = vec_rsqrt(vec4(1, 2, 3, 4));
	assert_flt_eq(1 / sqrtf(1), vec_x(v), 0.001);
	assert_flt_eq(1 / sqrtf(2), vec_y(v), 0.001);
	assert_flt_eq(1 / sqrtf(3), vec_z(v), 0.001);
	assert_flt_eq(1 / sqrtf(4), vec_w(v), 0.001);
} END_TEST

START_TEST(_vec_scale) {
	assert_vec_eq(vec3(1, 1, 1), vec_scale(vec3(1, 1, 1), 1));
	assert_vec_eq(vec3(2, 4, 6), vec_scale(vec3(1, 2, 3), 2));
	assert_vec_eq(vec3(-1, -1, -1), vec_scale(vec3(1, 1, 1), -1));
} END_TEST

START_TEST(_vec_scale_add) {
	assert_vec_eq(vec3(1, 1, 1), vec_scale_add(vec3(0, 0, 0), vec3(1, 1, 1), 1));
	assert_vec_eq(vec3(3, 6, 9), vec_scale_add(vec3(1, 2, 3), vec3(1, 2, 3), 2));
	assert_vec_eq(vec0(), vec_scale_add(vec0(), vec0(), 1));
} END_TEST

START_TEST(_vec_sqrt) {
	assert_vec_eq(vec3(1, 2, 3), vec_sqrt(vec3(1, 4, 9)));
	assert_vec_eq(vec3(4, 5, 7), vec_sqrt(vec3(16, 25, 49)));
	assert_vec_eq(vec3(sqrtf(2), sqrtf(3), sqrtf(5)), vec_sqrt(vec3(2, 3, 5)));
} END_TEST

START_TEST(_vec_subtract) {
	assert_vec_eq(vec_subtract(vec3(1, 2, 3), vec3(1, 1, 1)), vec3(0, 1, 2));
	assert_vec_eq(vec_subtract(vec3(1, 2, 3), vec3(0, 0, 0)), vec3(1, 2, 3));
	assert_vec_eq(vec_subtract(vec3(1, 2, 3), vec3(2, 3, 4)), vec3(-1, -1, -1));
} END_TEST

START_TEST(_vec_yzx) {
	assert_vec_eq(vec4(2, 3, 1, 4), vec_yzx(vec4(1, 2, 3, 4)));
} END_TEST

START_TEST(_vec_zxy) {
	assert_vec_eq(vec4(3, 1, 2, 4), vec_zxy(vec4(1, 2, 3, 4)));
} END_TEST

int main(int argc, char **argv) {

	TCase *tcase = tcase_create("vec");

	tcase_add_test(tcase, _vec0);
	tcase_add_test(tcase, _vec1);
	tcase_add_test(tcase, _vec2);
	tcase_add_test(tcase, _vec3);
	tcase_add_test(tcase, _vec4);
	tcase_add_test(tcase, _vec_add);
	tcase_add_test(tcase, _vec_cross);
	tcase_add_test(tcase, _vec_degrees);
	tcase_add_test(tcase, _vec_distance);
	tcase_add_test(tcase, _vec_divide);
	tcase_add_test(tcase, _vec_dot);
	tcase_add_test(tcase, _vec_equal);
	tcase_add_test(tcase, _vec_greater_than);
	tcase_add_test(tcase, _vec_greater_than_equal);
	tcase_add_test(tcase, _vec_length);
	tcase_add_test(tcase, _vec_less_than);
	tcase_add_test(tcase, _vec_less_than_equal);
	tcase_add_test(tcase, _vec_mix);
	tcase_add_test(tcase, _vec_multiply);
	tcase_add_test(tcase, _vec_negate);
	tcase_add_test(tcase, _vec_normalize);
	tcase_add_test(tcase, _vec_normalize_fast);
	tcase_add_test(tcase, _vec_not_equal);
	tcase_add_test(tcase, _vec_radians);
	tcase_add_test(tcase, _vec_random);
	tcase_add_test(tcase, _vec_random_range);
	tcase_add_test(tcase, _vec_rsqrt);
	tcase_add_test(tcase, _vec_scale);
	tcase_add_test(tcase, _vec_scale_add);
	tcase_add_test(tcase, _vec_sqrt);
	tcase_add_test(tcase, _vec_subtract);
	tcase_add_test(tcase, _vec_yzx);
	tcase_add_test(tcase, _vec_zxy);

	Suite *suite = suite_create("vec");
	suite_add_tcase(suite, tcase);

	SRunner *runner = srunner_create(suite);

	srunner_run_all(runner, CK_VERBOSE);
	int failed = srunner_ntests_failed(runner);

	srunner_free(runner);

	return failed;
}
