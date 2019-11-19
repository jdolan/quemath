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
#include <time.h>

#include "quemath.h"

#define TIME_BLOCK(name, block) { \
	const clock_t start = clock(); \
 	\
	block \
	\
	const clock_t end = clock(); \
	\
	printf("%s: %.9f seconds\n", name, (end - start) / (double) CLOCKS_PER_SEC); \
}

static vec *vectors(size_t count) {
	return calloc(count, sizeof(vec));
}

static vec *random_vectors(size_t count) {
	vec *v = vectors(count), *out = v;

	vec rand = vec4f(0xfeed, 0xdad, 0xdead, 0xbeef);
	for (size_t i = 0; i < count; i++) {
		*out++ = rand = vec_random(rand);
	}

	return v;
}

#define VectorAdd(a, b, c) (c[0] = a[0] + b[0], c[1] = a[1] + b[1], c[2] = a[2] + b[2], c[3] = a[3] + b[3])

START_TEST(_vec_add) {

	const int iterations = 10000000;
	vec *v = random_vectors(iterations);

	TIME_BLOCK("Vector add", {
		for (int i = 0; i < iterations; i++) {
			const float *a = (float *) &v[(i + 0) % iterations];
			const float *b = (float *) &v[(i + 1) % iterations];
			float *c = (float *) &v[(i + 2) % iterations];
			VectorAdd(a, b, c);
		}
	});

	free(v);
	v = random_vectors(iterations);

	TIME_BLOCK("Vector add SSE", {
		for (int i = 0; i < iterations; i++) {
			const vec a = v[(i + 0) % iterations];
			const vec b = v[(i + 1) % iterations];
			v[(i + 2) % iterations] = vec_add(a, b);
		}
	});

	free(v);

} END_TEST

#define DotProduct(a, b, c) (c[0] = a[0] * b[0] + a[1] * b[1] + a[2] * b[2])

START_TEST(_vec_dot) {

	const int iterations = 10000000;
	vec *v = random_vectors(iterations);

	TIME_BLOCK("Dot product", {
		for (int i = 0; i < iterations; i++) {
			const float *a = (float *) &v[(i + 0) % iterations];
			const float *b = (float *) &v[(i + 1) % iterations];
			float *c = (float *) &v[(i + 2) % iterations];
			DotProduct(a, b, c);
		}
	});

	free(v);
	v = random_vectors(iterations);

	TIME_BLOCK("Dot product SSE", {
		for (int i = 0; i < iterations; i++) {
			const vec a = v[(i + 0) % iterations];
			const vec b = v[(i + 1) % iterations];
			vec *c = &v[(i + 2) % iterations];
			*c = vec_dot3(a, b);
		}
	});

	free(v);

} END_TEST

static vec VectorNormalize(vec v) {

	const float length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (length) {
		const float ilength = 1.0 / length;
		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}

	return v;
}

START_TEST(_vec_normalize) {

	const int iterations = 10000000;
	vec *v = random_vectors(iterations);

	TIME_BLOCK("Vector normalize", {
		for (int i = 0; i < iterations; i++) {
			v[i] = VectorNormalize(v[i]);
		}
	});

	free(v);
	v = random_vectors(iterations);

	TIME_BLOCK("Vector normalize SSE", {
		for (int i = 0; i < iterations; i++) {
			v[i] = vec_normalize(v[i]);
		}
	});

	free(v);
	v = random_vectors(iterations);

	TIME_BLOCK("Vector normalize fast SSE", {
		for (int i = 0; i < iterations; i++) {
			v[i] = vec_normalize_fast(v[i]);
		}
	});

	free(v);

} END_TEST

static vec VectorScaleAdd(const vec a, const vec b, float scale) {
	return vec3f(a[0] + scale * b[0], a[1] + scale * b[1], a[2] + scale * b[2]);
}

START_TEST(_vec_scale_add) {

	const int iterations = 10000000;
	vec *v = random_vectors(iterations);

	TIME_BLOCK("Vector scale add", {
		for (int i = 0; i < iterations; i++) {
			const vec a = v[(i + 0) % iterations];
			const vec b = v[(i + 1) % iterations];
			v[(i + 2) % iterations] = VectorScaleAdd(a, b, 0.5);
		}
	});

	free(v);
	v = random_vectors(iterations);

	TIME_BLOCK("Vector scale add SSE", {
		for (int i = 0; i < iterations; i++) {
			const vec a = v[(i + 0) % iterations];
			const vec b = v[(i + 1) % iterations];
			v[(i + 2) % iterations] = vec_scale_add(a, b, 0.5);
		}
	});

	free(v);

} END_TEST

int main(int argc, char **argv) {

	TCase *tcase = tcase_create("vec");

	tcase_add_test(tcase, _vec_add);
	tcase_add_test(tcase, _vec_dot);
	tcase_add_test(tcase, _vec_normalize);
	tcase_add_test(tcase, _vec_scale_add);

	Suite *suite = suite_create("benchmark");
	suite_add_tcase(suite, tcase);

	SRunner *runner = srunner_create(suite);

	srunner_run_all(runner, CK_VERBOSE);
	int failed = srunner_ntests_failed(runner);

	srunner_free(runner);

	return failed;
}

