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

#pragma once

#include "vec.h"

/**
 * @brief Quaternions.
 */
typedef vec quat;

static inline quat quat4f(float x, float y, float z, float w);
static inline quat quat4fv(vec4 f);
static inline quat quat_add(const quat a, const quat b);
static inline ivec quat_compare_eq(const quat a, const quat b);
static inline ivec quat_compare_ne(const quat a, const quat b);
static inline int quat_equal(const quat a, const quat b);
static inline quat quat_euler(const vec angles);
static inline quat quat_identity(void);
static inline quat quat_inverse(const quat q);
static inline quat quat_look_at(const vec eye, const vec v);
static inline quat quat_multiply(const quat a, const quat b);
static inline quat quat_new(const vec axis, float angle);
static inline quat quat_normalize(const quat q);
static inline int quat_not_equal(const quat a, const quat b);
static inline quat quat_subtract(const quat a, const quat b);
static inline float quat_w(const quat q);
static inline float quat_x(const quat q);
static inline float quat_y(const quat q);
static inline float quat_z(const quat q);

static quat quat4f(float x, float y, float z, float w) {
	return vec4f(x, y, z, w);
}

static quat quat4fv(const vec4 f) {
	return vec4fv(f);
}

static quat quat_add(const quat a, const quat b) {
	return vec_add(a, b);
}

static ivec quat_compare_eq(const quat a, const quat b) {
	return vec_compare_eq(a, b);
}

static ivec quat_compare_ne(const quat a, const quat b) {
	return vec_compare_ne(a, b);
}

static int quat_equal(const quat a, const quat b) {
	return vec_equal(a, b);
}

static quat quat_euler(const vec angles) {

	const vec3 c = vec_vec3(vec_cosf(vec_scale(angles, 0.5)));
	const vec3 s = vec_vec3(vec_sinf(vec_scale(angles, 0.5)));

	return quat4f(
		c.x * c.y * c.z + s.x * s.y * s.z,
		s.x * c.y * c.z - c.x * s.y * s.z,
		c.x * s.y * c.z + s.x * c.y * s.z,
		c.x * c.y * s.z - s.x * s.y * c.z
	);
}

static quat quat_identity(void) {
	return quat4f(0, 0, 0, 1);
}

static quat quat_new(const vec axis, float angle) {

	const float s = sinf(angle * 0.5);
	const float c = cosf(angle * 0.5);

	return quat_normalize(vec_add(vec_scale(axis, s), vec4f(0, 0, 0, c)));
}

static quat quat_normalize(const quat q) {

	printf("%g %g %g %g\n", q[0], q[1], q[2], q[3]);
	if (vec_equal(vec_xyz(q), vec0())) {
		return quat_identity();
	} else {
		const vec dot = _mm_dp_ps(q, q, 0xFF);
		printf("dafuq %g\n", dot[0]);
		return vec_divide(q, vec_sqrt(_mm_dp_ps(q, q, 0xFF)));
	}
}

static int quat_not_equal(const quat a, const quat b) {
	return vec_not_equal(a, b);
}

static quat quat_subtract(const quat a, const quat b) {
	return vec_subtract(a, b);
}

/**
 * @return The fourth component of the quaternion @p q.
 */
static float quat_w(const quat q) {
	return vec_w(q);
}

/**
 * @return The first component of the quaternion @p q.
 */
static float quat_x(const quat q) {
	return vec_x(q);
}

/**
 * @return The second component of the quaternion @p q.
 */
static float quat_y(const quat q) {
	return vec_y(q);
}

/**
 * @return The third component of the quaternion @p q.
 */
static float quat_z(const quat q) {
	return vec_z(q);
}

