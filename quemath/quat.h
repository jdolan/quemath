/*
 * Quemath: An SSE optimized 3D math library for games.
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

static inline quat quat4(float x, float y, float z, float w);
static inline quat quat_add(const quat a, const quat b);
static inline quat quat_identity(void);
static inline quat quat_look_at(const vec eye, const vec v);
static inline quat quat_normalize(const quat q);
static inline quat quat_subtract(const quat a, const quat b);

static quat quat_normalize(const quat q) {

	const quat p = vec_normalize(q);
	if (ivec_equals(vec_compare_le(p, vec0()), ivec_true())) {
		return quat_identity();
	} else {
		return p;
	}
}
