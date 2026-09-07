/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef UNIASSERT_H
#define UNIASSERT_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cpp.h"

#define uniassert_ok_or_ret(ok, ...) \
	__uniassert_ok_or_ret ## __VA_OPT__(_1)(ok, ##__VA_ARGS__)

#define __uniassert_ok_or_ret(ok)		\
do {						\
	if (!(ok)) {				\
		__uniassert_failed("", #ok);	\
		return 1;			\
	}					\
} while (0)

#define __uniassert_ok_or_ret_1(ok, fmt, ...)			\
do {								\
	if (!(ok)) {						\
		__uniassert_failed(", " fmt, #ok, __VA_ARGS__);	\
		return 1;					\
	}							\
} while (0)

#define __uniassert_failed(fmt, ok, ...)				\
	fprintf(stderr, "%s:%d,%s(): assert %s failed" fmt "\n",	\
		__FILE__, __LINE__, __func__, ok, ##__VA_ARGS__)

#define uniassert_strequal(a, b) uniassert_ok_or_ret(!strcmp((a), (b)))
#define uniassert_strnequal(a, b, n) uniassert_ok_or_ret(!strncmp((a), (b), n))

#define uniassert_equal(a, b)						\
	uniassert_ok_or_ret((a) == (b), "%" PRIuMAX " != %" PRIuMAX,	\
			    (uintmax_t)(uintptr_t)(a),			\
			    (uintmax_t)(uintptr_t)(b))

#define uniassert_equal_signed(a, b)					\
	uniassert_ok_or_ret((a) == (b), "%" PRIdMAX " != %" PRIdMAX,	\
			    (intmax_t)(intptr_t)(a),			\
			    (intmax_t)(intptr_t)(b))

#define uniassert_is(x) uniassert_ok_or_ret(x)
#define uniassert_not(x) uniassert_ok_or_ret(!(x))

#define uniassert_ok(err) uniassert_not(err)
#define uniassert_no(err) uniassert_is(err)

#endif /* UNIASSERT_H */
