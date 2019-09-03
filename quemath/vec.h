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

#include "ivec.h"

/**
 * @defgroup vec vec
 * @brief Four component floating point vectors.
 * @{
 */

/**
 * @brief Four component floating point SSE vector type.
 */
typedef __m128 vec;

static inline ivec ivec_cast_vec(const vec v);
static inline ivec ivec_convert_vec(const vec v);

static inline vec vec0(void);
static inline vec vec1(float x);
static inline vec vec2(float x, float y);
static inline vec vec3(float x, float y, float z);
static inline vec vec4(float x, float y, float z, float w);
static inline vec vec_add(const vec a, const vec b);
static inline vec vec_cast_ivec(const ivec v);
static inline vec vec_convert_ivec(const ivec v);
static inline vec vec_cross(const vec a, const vec b);
static inline vec vec_degrees(const vec radians);
static inline vec vec_distance(const vec a, const vec b);
static inline vec vec_divide(const vec a, const vec b);
static inline vec vec_dot(const vec a, const vec b);
static inline ivec vec_compare_eq(const vec a, const vec b);
static inline ivec vec_compare_ge(const vec a, const vec b);
static inline ivec vec_compare_gt(const vec a, const vec b);
static inline ivec vec_compare_le(const vec a, const vec b);
static inline ivec vec_compare_lt(const vec a, const vec b);
static inline ivec vec_compare_ne(const vec a, const vec b);
static inline int vec_equals(const vec a, const vec b);
static inline int vec_greater_than(const vec a, const vec b);
static inline int vec_greater_than_equal(const vec a, const vec b);
static inline vec vec_length(const vec v);
static inline int vec_less_than(const vec a, const vec b);
static inline int vec_less_than_equal(const vec a, const vec b);
static inline vec vec_max(const vec a, const vec b);
static inline vec vec_min(const vec a, const vec b);
static inline vec vec_mix(const vec a, const vec b, float mix);
static inline vec vec_multiply(const vec a, const vec b);
static inline vec vec_negate(const vec v);
static inline vec vec_new(float f);
static inline vec vec_normalize(const vec v);
static inline vec vec_normalize_fast(const vec v);
static inline int vec_not_equal(const vec a, const vec b);
static inline vec vec_radians(const vec degrees);
static inline vec vec_random(vec last);
static inline vec vec_random_range(vec last, const vec mins, const vec maxs);
static inline vec vec_rsqrt(const vec v);
static inline vec vec_scale(const vec v, float scale);
static inline vec vec_scale_add(const vec a, const vec b, float scale);
static inline vec vec_sqrt(const vec v);
static inline vec vec_subtract(const vec a, const vec b);
static inline float vec_w(const vec v);
static inline float vec_x(const vec v);
static inline float vec_y(const vec v);
static inline float vec_z(const vec v);
static inline vec vec_yzx(const vec v);
static inline vec vec_zxy(const vec v);

/**
 * @brief Casts the floating point bit pattern of @p v to an integer vector.
 * @return The floating point bit pattern of @p v cast to an integer vector.
 */
static ivec ivec_cast_vec(const vec v) {
	return _mm_castps_si128(v);
}

/**
 * @brief Converts the vector @p v to its integer representation.
 * @return An integer vector containing the integer representation of @p v.
 */
static ivec ivec_convert_vec(const vec v) {
	return _mm_cvtps_epi32(v);
}

/**
 * @brief Creates a vector with all components initialized to zero.
 * @return A vector with all components initialized to zero.
 */
static vec vec0(void) {
	return _mm_setzero_ps();
}

/**
 * @brief Creates a vector with components `(x, 0, 0, 0)`.
 * @return A vector with components `(x, 0, 0, 0)`.
 */
static vec vec1(float x) {
	return _mm_set_ss(x);
}

/**
 * @brief Creates a vector with components `(x, y, 0, 0)`.
 * @return A vector with components `(x, y, 0, 0)`.
 */
static vec vec2(float x, float y) {
	return vec3(x, y, 0);
}

/**
 * @brief Creates a vector with components `(x, y, z, 0)`.
 * @return A vector with components `(x, y, z, 0)`.
 */
static vec vec3(float x, float y, float z) {
	return vec4(x, y, z, 0);
}

/**
 * @brief Creates a vector with components `(x, y, z, w)`.
 * @return A vector with components `(x, y, z, w)`.
 */
static vec vec4(float x, float y, float z, float w) {
	return _mm_setr_ps(x, y, z, w);
}

/**
 * @brief Calculates the sum of @p a `+` @p b.
 * @return A vector containing the sum of @p a `+` @p b.
 */
static vec vec_add(const vec a, const vec b) {
	return _mm_add_ps(a, b);
}

/**
 * @brief Casts the integer bit pattern of @p v to a vector.
 * @details No integer to floating point conversion is performed.
 * @return The integer bit pattern of @p v cast to a vector.
 */
static vec vec_cast_ivec(const ivec v) {
	return _mm_castsi128_ps(v);
}

/**
 * @brief Compares each component of the two vectors, testing `a[i] == b[i]`.
 * @details The comparison yields `0xFFFFFFFF` for true and `0x0` for false.
 * @return An integer vector containing the comparison result of @p a and @p b.
 */
static ivec vec_compare_eq(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmpeq_ps(a, b));
}

/**
 * @brief Compares each component of the two vectors, testing `a[i] >= b[i]`.
 * @details The comparison yields `0xFFFFFFFF` for true and `0x0` for false.
 * @return An integer vector containing the comparison result of @p a and @p b.
 */
static ivec vec_compare_ge(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmpge_ps(a, b));
}

/**
 * @brief Compares each component of the two vectors, testing `a[i] > b[i]`.
 * @details The comparison yields `0xFFFFFFFF` for true and `0x0` for false.
 * @return An integer vector containing the comparison result of @p a and @p b.
 */
static ivec vec_compare_gt(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmpgt_ps(a, b));
}

/**
 * @brief Compares each component of the two vectors, testing `a[i] <= b[i]`.
 * @details The comparison yields `0xFFFFFFFF` for true and `0x0` for false.
 * @return An integer vector containing the comparison result of @p a and @p b.
 */
static ivec vec_compare_le(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmple_ps(a, b));
}

/**
 * @brief Compares each component of the two vectors, testing `a[i] < b[i]`.
 * @details The comparison yields `0xFFFFFFFF` for true and `0x0` for false.
 * @return An integer vector containing the comparison result of @p a and @p b.
 */
static ivec vec_compare_lt(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmplt_ps(a, b));
}

/**
 * @brief Compares each component of the two vectors, testing `a[i] != b[i]`.
 * @details The comparison yields `0xFFFFFFFF` for true and `0x0` for false.
 * @return An integer vector containing the comparison result of @p a and @p b.
 */
static ivec vec_compare_ne(const vec a, const vec b) {
	return ivec_cast_vec(_mm_cmpneq_ps(a, b));
}

/**
 * @brief Converts the integer vector @p v to its floating point representation.
 * @return A vector containing the single precision floating point representation of @p v.
 */
static vec vec_convert_ivec(const ivec v) {
	return _mm_cvtepi32_ps(v);
}

/**
 * @brief Calculates the cross product of @p a `×` @p b.
 * @return A vector containing the cross product of @p a and @p b.
 */
static vec vec_cross(const vec a, const vec b) {
	// https://www.mathsisfun.com/algebra/vectors-cross-product.html
	return vec_subtract(
		vec_multiply(vec_yzx(a), vec_zxy(b)),
		vec_multiply(vec_zxy(a), vec_yzx(b))
	);
}

/**
 * @brief Converts the vector @p radians to degrees.
 * @return A vector containing the values of @p radians, converted to degrees.
 */
static vec vec_degrees(const vec radians) {
	return vec_scale(radians, 180 / M_PI);
}

/**
 * @brief Calculates the distance between the points @p a and @p b.
 * @return A vector `(d, 0, 0, 0)`, where `d` is the distance between points @p a and @p b.
 */
static vec vec_distance(const vec a, const vec b) {
	return vec_length(vec_subtract(b, a));
}

/**
 * @brief Calculates the quotient of @p a `÷` @p b.
 * @return A vector containing the quotient of @p a `/` @p b.
 */
static vec vec_divide(const vec a, const vec b) {
	return _mm_div_ps(a, b);
}

/**
 * @brief Calculates the product of @p a `·` @p b.
 * @return A vector `(d, 0, 0, 0)`, where `d` is the dot product of @p `·` @p b.
 */
static vec vec_dot(const vec a, const vec b) {
	return _mm_dp_ps(a, b, 0x71);
}

/**
 * @brief Reduces the comparison of `a == b` to an integer scalar.
 * @return `TRUE` if @p a is equal to @p b, `FALSE` otherwise.
 */
static int vec_equals(const vec a, const vec b) {
	return _mm_testc_si128(vec_compare_eq(a, b), ivec_true());
}

/**
 * @brief Reduces the comparison of `a > b` to an integer scalar.
 * @return `TRUE` if @p a is greater than @p b, `FALSE` otherwise.
 */
static int vec_greater_than(const vec a, const vec b) {
	return _mm_testc_si128(vec_compare_gt(a, b), ivec_true());
}

/**
 * @brief Reduces the comparison of `a >= b` to an integer scalar.
 * @return `TRUE` if @p a is greater than or equal to @p b, `FALSE` otherwise.
 */
static int vec_greater_than_equal(const vec a, const vec b) {
	return _mm_testc_si128(vec_compare_ge(a, b), ivec_true());
}

/**
 * @brief Calculates the length, or magnitude, of the vector @p v.
 * @return A vector `(l, 0, 0, 0)`, where `l` is the length of the vector @p v.
 */
static vec vec_length(const vec v) {
	return _mm_sqrt_ss(vec_dot(v, v));
}

/**
 * @brief Reduces the comparison of `a < b` to an integer scalar.
 * @return `TRUE` if @p a is less than @p b, `FALSE` otherwise.
 */
static int vec_less_than(const vec a, const vec b) {
	return _mm_testc_si128(vec_compare_lt(a, b), ivec_true());
}

/**
 * @brief Reduces the comparison of `a <= b` to an integer scalar.
 * @return `TRUE` if @p a is less than or equal to @p b, `FALSE` otherwise.
 */
static int vec_less_than_equal(const vec a, const vec b) {
	return _mm_testc_si128(vec_compare_le(a, b), ivec_true());
}

/**
 * @brief Calculates the maximum values of @p a and @p b.
 * @return A vector containing the maximum values of @p a and @p b.
 */
static vec vec_max(const vec a, const vec b) {
	return _mm_max_ps(a, b);
}

/**
 * @brief Calculates the minimum values of @p a and @p b.
 * @return A vector containing the minimum values of @p a and @p b.
 */
static vec vec_min(const vec a, const vec b) {
	return _mm_min_ps(a, b);
}

/**
 * @brief Linearly interpolates between vectors @p a and @p b.
 * @return A vector equal to `a * (1 - mix) + b * mix`.
 */
static vec vec_mix(const vec a, const vec b, float mix) {
	return vec_add(vec_scale(a, 1 - mix), vec_scale(b, mix));
}

/**
 * @brief Calculates the product of @p a `*` @p b.
 * @return A vector containing the product of @p a `*` @p b.
 */
static vec vec_multiply(const vec a, const vec b) {
	return _mm_mul_ps(a, b);
}

/**
 * @brief Returns the negated value of @p v.
 * @return A vector equal to the negated value of @p v.
 */
static vec vec_negate(const vec v) {
	return vec_subtract(vec0(), v);
}

/**
 * @brief Creates a vector with components `(f, f, f, f)`.
 * @return A vector with components `(f, f, f, f)`.
 */
static vec vec_new(float f) {
	return _mm_set1_ps(f);
}

/**
 * @brief Calculates the unit length vector of @p v by the square root.
 * @return A unit vector in the same direction of @p v.
 */
static vec vec_normalize(const vec v) {
	return _mm_div_ps(v, _mm_sqrt_ps(_mm_dp_ps(v, v, 0x7F)));
}

/**
 * @brief Calculates the approximate unit length vector of @p v by the inverse square root.
 * @return A unit vector approximation in the same direction of @p v.
 */
static vec vec_normalize_fast(const vec v) {
	return _mm_mul_ps(v, _mm_rsqrt_ps(_mm_dp_ps(v, v, 0x7F)));
}

/**
 * @brief Reduces the comparison of `a != b` to an integer scalar.
 * @return `TRUE` if @p a is not equal to @p b, `FALSE` otherwise.
 */
static int vec_not_equal(const vec a, const vec b) {
	return _mm_testc_si128(vec_compare_ne(a, b), ivec_true());
}

/**
 * @brief Converts the angles in @p degrees to radians.
 * @return A vector containing the values of @p degrees, converted to radians.
 */
static vec vec_radians(const vec degrees) {
	return vec_scale(degrees, M_PI / 180);
}

/**
 * @brief Generates a four component vector of random values using _Xorshift_.
 * @param last The last returned random vector, or a non-zero seed value.
 * @return A vector containing four psuedo-random values between `0` and `1`.
 */
static vec vec_random(vec last) {
	return vec_scale(vec_convert_ivec(ivec_random(ivec_cast_vec(last))), 1.0 / RAND_MAX);
}

/**
 * @brief Generates a four component vector of random values using _Xorshift_.
 * @param last The last returned random vector, or a non-zero seed value.
 * @param mins The lower bounds of the returned values (inclusive).
 * @param maxs The upper bounds of the returned values (exclusive).
 * @return A vector containing four psuedo-random values between `0` and `1`.
 */
static vec vec_random_range(vec last, const vec mins, const vec maxs) {
	return vec_add(mins, vec_multiply(vec_subtract(maxs, mins), vec_random(last)));
}

/**
 * @brief Calculates the approximate inverse square root of @p v.
 * @return A vector containing the approximate inverse square root of @p v.
 */
static vec vec_rsqrt(const vec v) {
	return _mm_rsqrt_ps(v);
}

/**
 * @brief Calculates the scalar product of @p v `*` @p scale.
 * @return A vector containing the scalar product @p v `*` @p scale.
 */
static vec vec_scale(const vec v, float scale) {
	return _mm_mul_ps(v, _mm_set1_ps(scale));
}

/**
 * @brief Calculates the sum of @p a and the scalar product @p b `*` @p scale.
 * @return A vector containing the sum of @p a and the scalar product @p b `*` @p scale.
 */
static vec vec_scale_add(const vec a, const vec b, float scale) {
	return vec_add(a, vec_scale(b, scale));
}

/**
 * @brief Calculates the square root of @p v.
 * @return A vector containing the square root of @p v.
 */
static vec vec_sqrt(const vec v) {
	return _mm_sqrt_ps(v);
}

/**
 * @brief Calculates the difference of @p a `-` @p b.
 * @return A vector containing the difference of @p a `-` @p b.
 */
static vec vec_subtract(const vec a, const vec b) {
	return _mm_sub_ps(a, b);
}

/**
 * @return The forth component of the vector @p v.
 */
static float vec_w(const vec v) {
	return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3)));
}

/**
 * @return The first component of the vector @p v.
 */
static float vec_x(const vec v) {
	return _mm_cvtss_f32(v);
}

/**
 * @return The second component of the vector @p v.
 */
static float vec_y(const vec v) {
	return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1)));
}

/**
 * @return The third component of the vector @p v.
 */
static float vec_z(const vec v) {
	return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2)));
}

/**
 * @return A swizzle, or shuffle vector `(y, z, x, w)` of the vector @p v.
 */
static vec vec_yzx(const vec v) {
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1));
}

/**
 * @return A swizzle, or shuffle vector `(z, x, y, w)` of the vector @p v.
 */
static vec vec_zxy(const vec v) {
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 1, 0, 2));
}

/**
 * @}
 */
