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
#include <math.h>

#include <ObjectivelyGL.h>

#define assert_flt_eq(a, b) ck_assert(fabsf(a - b) < __FLT_EPSILON__)
#define assert_vec_eq(a, b) \
{ \
	assert_flt_eq(a.x, b.x); \
	assert_flt_eq(a.y, b.y); \
	assert_flt_eq(a.z, b.z); \
	assert_flt_eq(a.w, b.w); \
}

START_TEST(_mat_identity) {
	mat m = mat_identity();
	assert_vec_eq(m.a, vec4f(1, 0, 0, 0));
	assert_vec_eq(m.b, vec4f(0, 1, 0, 0));
	assert_vec_eq(m.c, vec4f(0, 0, 1, 0));
	assert_vec_eq(m.d, vec4f(0, 0, 0, 1));
} END_TEST

START_TEST(_mat_translate) {
	mat m = mat_translate(1, 2, 3);
	assert_vec_eq(m.a, vec4f(0, 0, 0, 1));
	assert_vec_eq(m.b, vec4f(0, 0, 0, 2));
	assert_vec_eq(m.c, vec4f(0, 0, 0, 3));
	assert_vec_eq(m.d, vec4f(0, 0, 0, 0));


} END_TEST

int main(int argc, char **argv) {

	TCase *tcase = tcase_create("Matrix");

	tcase_add_test(tcase, _mat_identity);

	Suite *suite = suite_create("Matrix");
	suite_add_tcase(suite, tcase);

	SRunner *runner = srunner_create(suite);

	srunner_run_all(runner, CK_VERBOSE);
	int failed = srunner_ntests_failed(runner);

	srunner_free(runner);

	return failed;
}
