/*
 * ObjectivelyGL: Object oriented OpenGL framework for GNU C.
 * Copyright (C) 2014 Jay Dolan <jay@jaydolan.com>
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

#include "ivec.h"

static inline void assert_ivec_eq(const ivec a, const ivec b) {
	ck_assert_msg(ivec_equals(a, b), "(%d %d %d %d) == (%d %d %d %d)",
				  ivec_x(a), ivec_y(a), ivec_z(a), ivec_w(a),
				  ivec_x(b), ivec_y(b), ivec_z(b), ivec_w(b));
}

START_TEST(_ivec0) {
	assert_ivec_eq(ivec4(0, 0, 0, 0), ivec0());
} END_TEST

START_TEST(_ivec1) {
	assert_ivec_eq(ivec4(1, 0, 0, 0), ivec1(1));
} END_TEST

START_TEST(_ivec2) {
	assert_ivec_eq(ivec4(1, 2, 0, 0), ivec2(1, 2));
} END_TEST

START_TEST(_ivec3) {
	assert_ivec_eq(ivec4(1, 2, 3, 0), ivec3(1, 2, 3));
} END_TEST

START_TEST(_ivec4) {
	assert_ivec_eq(ivec4(1, 2, 3, 4), ivec4(1, 2, 3, 4));
} END_TEST

START_TEST(_ivec_abs) {
	assert_ivec_eq(ivec4(1, 2, 3, 4), ivec_abs(ivec4(-1, 2, -3, 4)));
} END_TEST

START_TEST(_ivec_add) {
	assert_ivec_eq(ivec3(2, 4, 6), ivec_add(ivec3(1, 2, 3), ivec3(1, 2, 3)));
} END_TEST

START_TEST(_ivec_equal) {
	assert_ivec_eq(ivec_true(), ivec_equal(ivec_new(1), ivec_new(1)));
	assert_ivec_eq(ivec_true(), ivec_equal(ivec3(1, 2, 3), ivec3(1, 2, 3)));
	assert_ivec_eq(ivec_false(), ivec_equal(ivec_new(1), ivec_new(2)));
} END_TEST

START_TEST(_ivec_greater_than) {
	assert_ivec_eq(ivec_true(), ivec_greater_than(ivec_new(1), ivec_new(0)));
	assert_ivec_eq(ivec_false(), ivec_greater_than(ivec_new(0), ivec_new(1)));
	assert_ivec_eq(ivec_false(), ivec_greater_than(ivec_new(0), ivec_new(0)));
} END_TEST

START_TEST(_ivec_less_than) {
	assert_ivec_eq(ivec_true(), ivec_less_than(ivec_new(0), ivec_new(1)));
	assert_ivec_eq(ivec_false(), ivec_less_than(ivec_new(1), ivec_new(0)));
	assert_ivec_eq(ivec_false(), ivec_less_than(ivec_new(0), ivec_new(0)));
} END_TEST

START_TEST(_ivec_random) {

	ivec min = ivec_new(RAND_MAX), max = ivec_new(0);

	ivec state = ivec4(0xfeed, 0xdad, 0xdead, 0xbeef);

	const int iterations = 1000;
	for (int i = 0; i < iterations; i++) {
		const ivec r = ivec_random(&state);
		min = ivec_min(r, min);
		max = ivec_max(r, max);
	}

	ck_assert_int_lt(ivec_x(min), RAND_MAX);
	ck_assert_int_lt(ivec_y(min), RAND_MAX);
	ck_assert_int_lt(ivec_z(min), RAND_MAX);
	ck_assert_int_lt(ivec_w(min), RAND_MAX);

	ck_assert_int_gt(ivec_x(max), 0);
	ck_assert_int_gt(ivec_y(max), 0);
	ck_assert_int_gt(ivec_z(max), 0);
	ck_assert_int_gt(ivec_w(max), 0);

} END_TEST

START_TEST(_ivec_random_range) {

	ivec state = ivec4(0xfeed, 0xdad, 0xdead, 0xbeef);

	const int iterations = 1000;
	for (int i = 0; i < iterations; i++) {
		const ivec r = ivec_random_range(&state, ivec_new(i), ivec_new(iterations));

		ck_assert_int_ge(ivec_x(r), i);
		ck_assert_int_ge(ivec_y(r), i);
		ck_assert_int_ge(ivec_z(r), i);
		ck_assert_int_ge(ivec_w(r), i);

		ck_assert_int_lt(ivec_x(r), iterations);
		ck_assert_int_lt(ivec_y(r), iterations);
		ck_assert_int_lt(ivec_z(r), iterations);
		ck_assert_int_lt(ivec_w(r), iterations);
	}

} END_TEST

int main(int argc, char **argv) {

	TCase *tcase = tcase_create("ivec");

	tcase_add_test(tcase, _ivec0);
	tcase_add_test(tcase, _ivec1);
	tcase_add_test(tcase, _ivec2);
	tcase_add_test(tcase, _ivec3);
	tcase_add_test(tcase, _ivec4);
	tcase_add_test(tcase, _ivec_abs);
	tcase_add_test(tcase, _ivec_add);
	tcase_add_test(tcase, _ivec_equal);
	tcase_add_test(tcase, _ivec_greater_than);
	tcase_add_test(tcase, _ivec_less_than);
	tcase_add_test(tcase, _ivec_random);
	tcase_add_test(tcase, _ivec_random_range);

	Suite *suite = suite_create("ivec");
	suite_add_tcase(suite, tcase);

	SRunner *runner = srunner_create(suite);

	srunner_run_all(runner, CK_VERBOSE);
	int failed = srunner_ntests_failed(runner);

	srunner_free(runner);

	return failed;
}

