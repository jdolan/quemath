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

typedef union {
	/**
	 * @brief The 128 bit integer SSE vector.
	 */
	__m128i ivec;

	/**
	 * @brief Component accessors.
	 */
	struct {
		int i, j, k, l;
	};
} ivec;

static inline ivec ivec1(int i);
static inline ivec ivec2(int i, int j);
static inline ivec ivec3(int i, int j, int k);
static inline ivec ivec4(int i, int j, int k, int l);
static inline ivec ivec_abs(const ivec v);
static inline ivec ivec_add(const ivec a, const ivec b);
static inline ivec ivec_equal(const ivec a, const ivec b);
static inline int ivec_equals(const ivec a, const ivec b);
static inline ivec ivec_false(void);
static inline ivec ivec_greater_than(const ivec a, const ivec b);
static inline ivec ivec_less_than(const ivec a, const ivec b);
static inline ivec ivec_max(const ivec a, const ivec b);
static inline ivec ivec_min(const ivec a, const ivec b);
static inline ivec ivec_multiply(const ivec a, const ivec b);
static inline ivec ivec_new(int i);
static inline ivec ivec_subtract(const ivec a, const ivec b);
static inline ivec ivec_true(void);

static ivec ivec1(int i) {
	return ivec2(i, 0);
}

static ivec ivec2(int i, int j) {
	return ivec3(i, j, 0);
}

static ivec ivec3(int i, int j, int k) {
	return ivec4(i, j, k, 0);
}

static ivec ivec4(int i, int j, int k, int l) {
	return (ivec) _mm_setr_epi32(i, j, k, l);
}

static ivec ivec_abs(const ivec v) {
	return (ivec) _mm_abs_epi32(v.ivec);
}

static ivec ivec_add(const ivec a, const ivec b) {
	return (ivec) _mm_add_epi32(a.ivec, b.ivec);
}

static ivec ivec_equal(const ivec a, const ivec b) {
	return (ivec) _mm_cmpeq_epi32(a.ivec, b.ivec);
}

static ivec ivec_false(void) {
	return (ivec) _mm_setzero_si128();
}

static int ivec_equals(const ivec a, const ivec b) {
	return _mm_testc_si128(ivec_equal(a, b).ivec, ivec_true().ivec);
}

static ivec ivec_greater_than(const ivec a, const ivec b) {
	return (ivec) _mm_cmpgt_epi32(a.ivec, b.ivec);
}

static ivec ivec_less_than(const ivec a, const ivec b) {
	return (ivec) _mm_cmplt_epi32(a.ivec, b.ivec);
}

static ivec ivec_max(const ivec a, const ivec b) {
	return (ivec) _mm_max_epi32(a.ivec, b.ivec);
}

static ivec ivec_min(const ivec a, const ivec b) {
	return (ivec) _mm_min_epi32(a.ivec, b.ivec);
}

static ivec ivec_multiply(const ivec a, const ivec b) {
	return (ivec) _mm_mul_epi32(a.ivec, b.ivec);
}

static ivec ivec_new(int i) {
	return (ivec) _mm_set1_epi32(i);
}

static ivec ivec_subtract(const ivec a, const ivec b) {
	return (ivec) _mm_sub_epi32(a.ivec, b.ivec);
}

static ivec ivec_true(void) {
	return (ivec) _mm_set1_epi32(0xFFFFFFFF);
}
