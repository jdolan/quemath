/*
 * Quemath: An SSE optimized math library for games, written in C99.
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

#include "quat.h"

static inline void assert_quat_eq(const vec a, const vec b) {
	ck_assert_msg(quat_equals(a, b), "(%g, %g, %g, %g) == (%g, %g, %g, %g)",
				  quat_x(a), quat_y(a), quat_z(a), quat_w(a),
				  quat_x(b), quat_y(b), quat_z(b), quat_w(b));
}

START_TEST(_quat0) {
	assert_quat_eq(quat4(0, 0, 0, 0), quat0());
} END_TEST

START_TEST(_quat1) {
	assert_quat_eq(quat4(1, 0, 0, 0), quat1(1));
} END_TEST

START_TEST(_quat2) {
	assert_quat_eq(quat4(1, 2, 0, 0), quat2(1, 2));
} END_TEST

START_TEST(_quat3) {
	assert_quat_eq(quat4(1, 2, 3, 0), quat3(1, 2, 3));
} END_TEST

START_TEST(_quat4) {
	assert_quat_eq(quat4(1, 2, 3, 4), quat4(1, 2, 3, 4));
} END_TEST


int main(int argc, char **argv) {

	TCase *tcase = tcase_create("quat");

	tcase_add_test(tcase, _quat0);
	tcase_add_test(tcase, _quat1);
	tcase_add_test(tcase, _quat2);
	tcase_add_test(tcase, _quat3);
	tcase_add_test(tcase, _quat4);
	tcase_add_test(tcase, _quat_abs);
	tcase_add_test(tcase, _quat_add);
	tcase_add_test(tcase, _quat_equal);

	Suite *suite = suite_create("quat");
	suite_add_tcase(suite, tcase);

	SRunner *runner = srunner_create(suite);

	srunner_run_all(runner, CK_VERBOSE);
	int failed = srunner_ntests_failed(runner);

	srunner_free(runner);

	return failed;
}

