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

#include <math.h>
#include <x86intrin.h>

/**
 * @defgroup ivec ivec
 * @brief Four component integer vectors.
 * @{
 */

/**
 * @brief Four component integer SSE vector type.
 */
typedef __m128i ivec;

static inline ivec ivec0(void);
static inline ivec ivec1(int x);
static inline ivec ivec2(int x, int y);
static inline ivec ivec3(int x, int y, int z);
static inline ivec ivec4(int x, int y, int z, int w);
static inline ivec ivec_abs(const ivec v);
static inline ivec ivec_add(const ivec a, const ivec b);
static inline ivec ivec_compare_eq(const ivec a, const ivec b);
static inline ivec ivec_compare_gt(const ivec a, const ivec b);
static inline ivec ivec_compare_lt(const ivec a, const ivec b);
static inline int ivec_equals(const ivec a, const ivec b);
static inline ivec ivec_false(void);
static inline int ivec_greater_than(const ivec a, const ivec b);
static inline int ivec_less_than(const ivec a, const ivec b);
static inline ivec ivec_max(const ivec a, const ivec b);
static inline ivec ivec_min(const ivec a, const ivec b);
static inline ivec ivec_modulo(const ivec a, const ivec b);
static inline ivec ivec_multiply(const ivec a, const ivec b);
static inline ivec ivec_new(int i);
static inline ivec ivec_random(ivec last);
static inline ivec ivec_random_range(ivec last, ivec mins, ivec maxs);
static inline ivec ivec_subtract(const ivec a, const ivec b);
static inline ivec ivec_true(void);
static inline int ivec_w(const ivec v);
static inline int ivec_x(const ivec v);
static inline int ivec_y(const ivec v);
static inline int ivec_z(const ivec v);

/**
 * @return An integer vector with all components initialized to zero.
 */
static ivec ivec0(void) {
	return _mm_setzero_si128();
}

/**
 * @return An integer vector with components `(x, 0, 0, 0)`.
 */
static ivec ivec1(int x) {
	return ivec2(x, 0);
}

/**
 * @return An integer vector with components `(x, y, 0, 0)`.
 */
static ivec ivec2(int x, int y) {
	return ivec3(x, y, 0);
}

/**
 * @return An integer vector with components `(x, y, z, 0)`.
 */
static ivec ivec3(int x, int y, int z) {
	return ivec4(x, y, z, 0);
}

/**
 * @return An integer vector with components `(x, y, z, w)`.
 */
static ivec ivec4(int x, int y, int z, int w) {
	return _mm_setr_epi32(x, y, z, w);
}

/**
 * @return An integer vector with each component containing the absolute value
 * of the corresponding component in @p v.
 */
static ivec ivec_abs(const ivec v) {
	return _mm_abs_epi32(v);
}

/**
 * @return An integer vector containing the sum @p a `+` @p b.
 */
static ivec ivec_add(const ivec a, const ivec b) {
	return _mm_add_epi32(a, b);
}

/**
 * @brief Compares each component of the two integer vectors, testing `a[i] == b[i]`.
 * @details The comparison yields `0xFFFFFFFF` for true and `0x0` for false.
 * @return An integer vector containing the comparison result of @p a and @p b.
 */
static ivec ivec_compare_eq(const ivec a, const ivec b) {
	return _mm_cmpeq_epi32(a, b);
}

/**
 * @brief Compares each component of the two integer vectors, testing `a[i] > b[i]`.
 * @details The comparison yields `0xFFFFFFFF` for true and `0x0` for false.
 * @return An integer vector containing the comparison result of @p a and @p b.
 */
static ivec ivec_compare_gt(const ivec a, const ivec b) {
	return _mm_cmpgt_epi32(a, b);
}

/**
 * @brief Compares each component of the two integer vectors, testing `a[i] < b[i]`.
 * @details The comparison yields `0xFFFFFFFF` for true and `0x0` for false.
 * @return An integer vector containing the comparison result of @p a and @p b.
 */
static ivec ivec_compare_lt(const ivec a, const ivec b) {
	return _mm_cmplt_epi32(a, b);
}

/**
 * @return An integer vector with all four components initialized to false (`0x0`).
 */
static ivec ivec_false(void) {
	return _mm_setzero_si128();
}

/**
 * @brief Reduces the comparison of `a == b` to an integer scalar.
 * @return `TRUE` if @p a is equal to @p b, `FALSE` otherwise.
 */
static int ivec_equals(const ivec a, const ivec b) {
	return _mm_testc_si128(ivec_compare_eq(a, b), ivec_true());
}

/**
 * @brief Reduces the comparison of `a > b` to an integer scalar.
 * @return `TRUE` if @p a is greater than @p b, `FALSE` otherwise.
 */
static int ivec_greater_than(const ivec a, const ivec b) {
	return _mm_testc_si128(ivec_compare_gt(a, b), ivec_true());
}

/**
 * @brief Reduces the comparison of `a < b` to an integer scalar.
 * @return `TRUE` if @p a is less than @p b, `FALSE` otherwise.
 */
static int ivec_less_than(const ivec a, const ivec b) {
	return _mm_testc_si128(ivec_compare_lt(a, b), ivec_true());
}

/**
 * @return An integer vector containing the maximum components of @p a and @p b.
 */
static ivec ivec_max(const ivec a, const ivec b) {
	return _mm_max_epi32(a, b);
}

/**
 * @return An integer vector containing the minimum components of @p a and @p b.
 */
static ivec ivec_min(const ivec a, const ivec b) {
	return _mm_min_epi32(a, b);
}

/**
 * @return An integer vector containing the modulo of @p a `%` @p b.
 */
static ivec ivec_modulo(const ivec a, const ivec b) {
	return ivec4(ivec_x(a) % ivec_x(b),
				 ivec_y(a) % ivec_y(b),
				 ivec_z(a) % ivec_z(b),
				 ivec_w(a) % ivec_w(b));
}

/**
 * @return An integer vector containing the product of @p a `*` @p b.
 */
static ivec ivec_multiply(const ivec a, const ivec b) {
	return _mm_mul_epi32(a, b);
}

/**
 * @return An integer vector with components `(i, i, i, i)`.
 */
static ivec ivec_new(int i) {
	return _mm_set1_epi32(i);
}

/**
 * @brief Generates a four component vector of random integers using _Xorshift_.
 * @param last The last returned random integer vector, or a non-zero seed value.
 * @return An integer vector containing four psuedo-random numbers between `0` and `RAND_MAX`.
 */
static ivec ivec_random(ivec last) {
	last = _mm_xor_si128(last, _mm_slli_epi32(last, 13));
	last = _mm_xor_si128(last, _mm_srli_epi32(last, 17));
	last = _mm_xor_si128(last, _mm_slli_epi32(last,  5));
	last = _mm_and_si128(last, _mm_set1_epi32(RAND_MAX));
	return last;
}

/**
 * @brief Generates a four component vector of random integers using _Xorshift_.
 * @param last The last returned random integer vector, or a non-zero seed value.
 * @param mins The lower bounds of the returned integers (inclusive).
 * @param maxs The upper bounds of the returned integers (exclusive).
 * @return An integer vector containing four psuedo-random numbers between @p mins and @p maxs.
 */
static ivec ivec_random_range(ivec last, ivec mins, ivec maxs) {
	return ivec_add(mins, ivec_modulo(ivec_random(last), ivec_subtract(maxs, mins)));
}

/**
 * @return An integer vector containing the difference of @p a `-` @p b.
 */
static ivec ivec_subtract(const ivec a, const ivec b) {
	return _mm_sub_epi32(a, b);
}

/**
 * @return An integer vector with all four components initialized to true (`0xFFFFFFFF`).
 */
static ivec ivec_true(void) {
	return _mm_set1_epi32(0xFFFFFFFF);
}

/**
 * @return The forth component of the integer vector @p v.
 */
static int ivec_w(const ivec v) {
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(v, _MM_SHUFFLE(3, 3, 3, 3)));
}


/**
 * @return The first component of the integer vector @p v.
 */
static int ivec_x(const ivec v) {
	return _mm_cvtsi128_si32(v);
}

/**
 * @return The second component of the integer vector @p v.
 */
static int ivec_y(const ivec v) {
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(v, _MM_SHUFFLE(1, 1, 1, 1)));
}

/**
 * @return The third component of the integer vector @p v.
 */
static int ivec_z(const ivec v) {
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(v, _MM_SHUFFLE(2, 2, 2, 2)));
}

/** @} */
