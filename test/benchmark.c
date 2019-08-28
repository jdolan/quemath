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
#include <time.h>

#include "quemath.h"

#define TIME_BLOCK(name, block) { \
	const clock_t start = clock(); \
 	\
	block \
	\
	const clock_t end = clock(); \
	\
	printf("%s: %g seconds\n", name, (end - start) / (double) CLOCKS_PER_SEC); \
}

static vec *random_vectors(size_t count) {

	vec *vectors = calloc(count, sizeof(vec));
	vec state = vec4(0xfeed, 0xdad, 0xdead, 0xbeef);

	vec *out = vectors;
	for (size_t i = 0; i < count; i++) {
		*out++ = vec_random(&state);
	}

	return vectors;
}

#define VectorAdd(a,b,c) (c[0] = a[0] + b[0], c[1] = a[1] + b[1], c[2] = a[2] + b[2], c[3] = a[3] + b[3])

START_TEST(_vec_add) {

	const int iterations = 1000000;
	vec *vectors = random_vectors(iterations);

	TIME_BLOCK("Vector add, CPU", {
		for (int i = 0; i < iterations; i++) {
			const float *a = (float *) &vectors[(i + 0) % iterations];
			const float *b = (float *) &vectors[(i + 1) % iterations];
			float *c = (float *) &vectors[(i + 2) % iterations];
			VectorAdd(a, b, c);
		}
	});

	free(vectors);
	vectors = random_vectors(iterations);

	TIME_BLOCK("Vector add, SIMD", {
		for (int i = 0; i < iterations; i++) {
			const vec a = vectors[(i + 0) % iterations];
			const vec b = vectors[(i + 1) % iterations];
			vec c = vectors[(i + 2) % iterations];
			c = vec_add(a, b);
		}
	});

	free(vectors);

} END_TEST

#define DotProduct(x, y) (x[0] * y[0] + x[1] * y[1] + x[2] * y[2])

START_TEST(_vec_dot) {

	const int iterations = 1000000;
	vec *vectors = random_vectors(iterations);

	TIME_BLOCK("Dot product, CPU", {
		for (int i = 0; i < iterations; i++) {
			const float *a = (float *) &vectors[(i + 0) % iterations];
			const float *b = (float *) &vectors[(i + 1) % iterations];
			float *c = (float *) &vectors[(i + 2) % iterations];
			*c = DotProduct(a, b);
		}
	});

	free(vectors);
	vectors = random_vectors(iterations);

	TIME_BLOCK("Dot product, SIMD", {
		for (int i = 0; i < iterations; i++) {
			const vec a = vectors[(i + 0) % iterations];
			const vec b = vectors[(i + 1) % iterations];
			vec c = vectors[(i + 2) % iterations];
			c = vec_dot(a, b);
		}
	});

	free(vectors);

} END_TEST

static float VectorNormalize(float v[3]) {

	const float length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (length) {
		const float ilength = 1.0 / length;
		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}

	return length;
}

START_TEST(_vec_normalize) {

	const int iterations = 1000000;
	vec *vectors = random_vectors(iterations);

	TIME_BLOCK("Vector normalize, CPU", {
		for (int i = 0; i < iterations; i++) {
			VectorNormalize((float *) &vectors[i]);
		}
	});

	free(vectors);
	vectors = random_vectors(iterations);

	TIME_BLOCK("Vector normalize, SIMD", {
		for (int i = 0; i < iterations; i++) {
			vectors[i] = vec_normalize(vectors[i]);
		}
	});

	free(vectors);

} END_TEST

int main(int argc, char **argv) {

	TCase *tcase = tcase_create("vec");

	tcase_add_test(tcase, _vec_add);
	tcase_add_test(tcase, _vec_dot);
	tcase_add_test(tcase, _vec_normalize);

	Suite *suite = suite_create("benchmark");
	suite_add_tcase(suite, tcase);

	SRunner *runner = srunner_create(suite);

	srunner_run_all(runner, CK_VERBOSE);
	int failed = srunner_ntests_failed(runner);

	srunner_free(runner);

	return failed;
}

