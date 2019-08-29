/*
 * Quemath: An SSE4 optimized 3D math library for games.
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

#include <math.h>
#include <x86intrin.h>

#include "ivec.h"

/**
 * @brief Four component floating point SSE vector type.
 */
typedef __m128 vec;

static inline vec vec0(void);
static inline vec vec1(float x);
static inline vec vec2(float x, float y);
static inline vec vec3(float x, float y, float z);
static inline vec vec4(float x, float y, float z, float w);
static inline vec vec_add(const vec a, const vec b);
static inline ivec ivec_cast_vec(const vec v);
static inline vec vec_cast_ivec(const ivec v);
static inline ivec ivec_convert_vec(const vec v);
static inline vec vec_convert_ivec(const ivec v);
static inline vec vec_cross(const vec a, const vec b);
static inline vec vec_degrees(const vec radians);
static inline vec vec_distance(const vec a, const vec b);
static inline vec vec_divide(const vec a, const vec b);
static inline vec vec_dot(const vec a, const vec b);
static inline ivec vec_equal(const vec a, const vec b);
static inline int vec_equals(const vec a, const vec b);
static inline ivec vec_greater_than(const vec a, const vec b);
static inline ivec vec_greater_than_equal(const vec a, const vec b);
static inline vec vec_length(const vec v);
static inline ivec vec_less_than(const vec a, const vec b);
static inline ivec vec_less_than_equal(const vec a, const vec b);
static inline vec vec_max(const vec a, const vec b);
static inline vec vec_min(const vec a, const vec b);
static inline vec vec_mix(const vec a, const vec b, float mix);
static inline vec vec_multiply(const vec a, const vec b);
static inline vec vec_negate(const vec v);
static inline vec vec_new(float f);
static inline vec vec_normalize(const vec v);
static inline vec vec_normalize_fast(const vec v);
static inline ivec vec_not_equal(const vec a, const vec b);
static inline vec vec_radians(const vec degrees);
static inline vec vec_random(vec *state);
static inline vec vec_random_range(vec *state, const vec mins, const vec maxs);
static inline vec vec_rsqrt(const vec v);
static inline vec vec_scale(const vec v, float scale);
static inline vec vec_scale_add(const vec a, const vec b, float scale);
static inline vec vec_sqrt(const vec v);
static inline vec vec_subtract(const vec a, const vec b);
static inline float vec_x(const vec v);
static inline float vec_y(const vec v);
static inline float vec_z(const vec v);
static inline float vec_w(const vec v);
static inline vec vec_yzx(const vec v);
static inline vec vec_zxy(const vec v);

static vec vec0(void) {
	return _mm_setzero_ps();
}

static vec vec1(float x) {
	return _mm_set_ss(x);
}

static vec vec2(float x, float y) {
	return vec3(x, y, 0);
}

static vec vec3(float x, float y, float z) {
	return vec4(x, y, z, 0);
}

static vec vec4(float x, float y, float z, float w) {
	return _mm_setr_ps(x, y, z, w);
}

static vec vec_add(const vec a, const vec b) {
	return _mm_add_ps(a, b);
}

static ivec ivec_cast_vec(const vec v) {
	return (ivec) _mm_castps_si128(v);
}

static vec vec_cast_ivec(const ivec v) {
	return _mm_castsi128_ps(v);
}

static ivec ivec_convert_vec(const vec v) {
	return (ivec) _mm_cvtps_epi32(v);
}

static vec vec_convert_ivec(const ivec v) {
	return _mm_cvtepi32_ps(v);
}

static vec vec_cross(const vec a, const vec b) {
	// https://www.mathsisfun.com/algebra/vectors-cross-product.html
	return vec_subtract(
		vec_multiply(vec_yzx(a), vec_zxy(b)),
		vec_multiply(vec_zxy(a), vec_yzx(b))
	);
}

static vec vec_degrees(const vec radians) {
	return vec_scale(radians, 180 / M_PI);
}

static vec vec_distance(const vec a, const vec b) {
	return vec_length(vec_subtract(b, a));
}

static vec vec_divide(const vec a, const vec b) {
	return _mm_div_ps(a, b);
}

static vec vec_dot(const vec a, const vec b) {
	return _mm_dp_ps(a, b, 0x71);
}

static ivec vec_equal(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmpeq_ps(a, b));
}

static int vec_equals(const vec a, const vec b) {
	return _mm_testc_si128(vec_equal(a, b), ivec_true());
}

static ivec vec_greater_than(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmpgt_ps(a, b));
}

static ivec vec_greater_than_equal(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmpge_ps(a, b));
}

static vec vec_length(const vec v) {
	return _mm_sqrt_ss(vec_dot(v, v));
}

static ivec vec_less_than(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmplt_ps(a, b));
}

static ivec vec_less_than_equal(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmple_ps(a, b));
}

static vec vec_max(const vec a, const vec b) {
	return _mm_max_ps(a, b);
}

static vec vec_min(const vec a, const vec b) {
	return _mm_min_ps(a, b);
}

static vec vec_mix(const vec a, const vec b, float mix) {
	return vec_add(vec_scale(a, 1 - mix), vec_scale(b, mix));
}

static vec vec_multiply(const vec a, const vec b) {
	return _mm_mul_ps(a, b);
}

static vec vec_negate(const vec v) {
	return vec_subtract(vec0(), v);
}

static vec vec_new(float f) {
	return _mm_set1_ps(f);
}

static vec vec_normalize(const vec v) {
	return _mm_div_ps(v, _mm_sqrt_ps(_mm_dp_ps(v, v, 0x7F)));
}

static vec vec_normalize_fast(const vec v) {
	return _mm_mul_ps(v, _mm_rsqrt_ps(_mm_dp_ps(v, v, 0x7F)));
}

static ivec vec_not_equal(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmpneq_ps(a, b));
}

static vec vec_radians(const vec degrees) {
	return vec_scale(degrees, M_PI / 180);
}

static vec vec_random(vec *state) {
	ivec s = ivec_cast_vec(*state);
	ivec r = ivec_random(&s);

	*state = vec_cast_ivec(r);

	return vec_scale(vec_convert_ivec(r), 1.0 / RAND_MAX);
}

static vec vec_random_range(vec *state, const vec mins, const vec maxs) {
	return vec_add(mins, vec_multiply(vec_subtract(maxs, mins), vec_random(state)));
}

static vec vec_rsqrt(const vec v) {
	return _mm_rsqrt_ps(v);
}

static vec vec_scale(const vec v, float scale) {
	return _mm_mul_ps(v, _mm_set1_ps(scale));
}

static vec vec_scale_add(const vec a, const vec b, float scale) {
	return vec_add(a, vec_scale(b, scale));
}

static vec vec_sqrt(const vec v) {
	return _mm_sqrt_ps(v);
}

static vec vec_subtract(const vec a, const vec b) {
	return _mm_sub_ps(a, b);
}

static float vec_x(const vec v) {
	return _mm_cvtss_f32(v);
}

static float vec_y(const vec v) {
	return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1)));
}

static float vec_z(const vec v) {
	return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2)));
}

static float vec_w(const vec v) {
	return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3)));
}

static vec vec_yzx(const vec v) {
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1));
}

static vec vec_zxy(const vec v) {
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 1, 0, 2));
}

