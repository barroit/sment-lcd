// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>

#include "strtox.h"
#include "uniassert.h"
#include "unitest.h"

#define expect_unsigned(type, fn, str, base, expect)			\
do {									\
	type res = 0;							\
									\
	errno = 0;							\
	uniassert_equal_signed(fn(str, base, &res), 0);			\
	uniassert_ok_or_ret((uintmax_t)res == (uintmax_t)(expect),	\
			    "%" PRIuMAX " != %" PRIuMAX,		\
			    (uintmax_t)res, (uintmax_t)(expect));	\
	uniassert_equal_signed(errno, 0);				\
} while (0)

#define expect_signed(type, fn, str, base, expect)			\
do {									\
	type res = 0;							\
									\
	errno = 0;							\
	uniassert_equal_signed(fn(str, base, &res), 0);			\
	uniassert_ok_or_ret((intmax_t)res == (intmax_t)(expect),	\
			    "%" PRIdMAX " != %" PRIdMAX,		\
			    (intmax_t)res, (intmax_t)(expect));		\
	uniassert_equal_signed(errno, 0);				\
} while (0)

#define expect_error(type, fn, str, base, errnum)			\
do {									\
	type res = (type)0x5a;						\
									\
	errno = 0;							\
	uniassert_equal_signed(fn(str, base, &res), -1);		\
	uniassert_equal_signed(errno, (errnum));			\
	uniassert_ok_or_ret(res == (type)0x5a);				\
} while (0)

unitest_begin();

unitest_routine(strxtoull_parse)
{
	expect_unsigned(unsigned long long, strxtoull, "42", 0, 42ull);
	expect_unsigned(unsigned long long, strxtoull, "052", 0, 42ull);
	expect_unsigned(unsigned long long, strxtoull, "0x2a", 0, 42ull);
	expect_unsigned(unsigned long long, strxtoull, "+0x2a", 0, 42ull);
	expect_unsigned(unsigned long long, strxtoull, "101010", 2, 42ull);
	expect_unsigned(unsigned long long, strxtoull, "2a", 16, 42ull);
	return 0;
}

unitest_routine(strxtoull_invalid)
{
	expect_error(unsigned long long, strxtoull, "", 0, EINVAL);
	expect_error(unsigned long long, strxtoull, "+", 0, EINVAL);
	expect_error(unsigned long long, strxtoull, "0x", 0, EINVAL);
	expect_error(unsigned long long, strxtoull, "08", 0, EINVAL);
	expect_error(unsigned long long, strxtoull, "12x", 10, EINVAL);
	expect_error(unsigned long long, strxtoull, " 12", 10, EINVAL);
	expect_error(unsigned long long, strxtoull, "12 ", 10, EINVAL);
	return 0;
}

unitest_routine(strxtoull_range)
{
	expect_unsigned(unsigned long long, strxtoull,
			"18446744073709551615", 10, ULLONG_MAX);
	expect_error(unsigned long long, strxtoull,
		     "18446744073709551616", 10, ERANGE);
	return 0;
}

unitest_routine(strxto_unsigned_negative)
{
	expect_unsigned(unsigned long long, strxtoull, "-1", 10, ULLONG_MAX);
	expect_unsigned(unsigned long long, strxtoull, "-42", 10,
			ULLONG_MAX - 41);
	expect_unsigned(uint64_t, strxtou64, "-1", 10, UINT64_MAX);
	expect_unsigned(unsigned long, strxtoul, "-1", 10, ULONG_MAX);
	expect_unsigned(unsigned long, strxtoul, "-42", 10, ULONG_MAX - 41);
	expect_unsigned(unsigned int, strxtou, "-1", 10, UINT_MAX);
	expect_unsigned(unsigned int, strxtou, "-42", 10, UINT_MAX - 41);
	expect_unsigned(uint32_t, strxtou32, "-1", 10, UINT32_MAX);
	expect_unsigned(uint32_t, strxtou32, "-42", 10, UINT32_MAX - 41);
	expect_unsigned(uint16_t, strxtou16, "-1", 10, UINT16_MAX);
	expect_unsigned(uint16_t, strxtou16, "-42", 10, UINT16_MAX - 41);
	expect_unsigned(uint8_t, strxtou8, "-1", 10, UINT8_MAX);
	expect_unsigned(uint8_t, strxtou8, "-42", 10, UINT8_MAX - 41);

	expect_error(uint32_t, strxtou32, "-4294967296", 10, ERANGE);
	expect_error(uint16_t, strxtou16, "-65536", 10, ERANGE);
	expect_error(uint8_t, strxtou8, "-256", 10, ERANGE);
	return 0;
}

unitest_routine(strxtoll_parse)
{
	expect_signed(long long, strxtoll, "42", 0, 42ll);
	expect_signed(long long, strxtoll, "+42", 0, 42ll);
	expect_signed(long long, strxtoll, "-42", 0, -42ll);
	expect_signed(long long, strxtoll, "-0x2a", 0, -42ll);
	return 0;
}

unitest_routine(strxtoll_range)
{
	expect_signed(long long, strxtoll, "9223372036854775807", 10,
		      LLONG_MAX);
	expect_signed(long long, strxtoll, "-9223372036854775808", 10,
		      LLONG_MIN);

	expect_error(long long, strxtoll, "9223372036854775808", 10, ERANGE);
	expect_error(long long, strxtoll, "-9223372036854775809", 10, ERANGE);
	return 0;
}

unitest_routine(strxto_native_unsigned)
{
	expect_unsigned(unsigned long, strxtoul, "0x2a", 0, 42ul);
	expect_unsigned(unsigned int, strxtou, "052", 0, 42u);
	return 0;
}

unitest_routine(strxto_native_signed)
{
	expect_signed(long, strxtol, "-42", 10, -42l);
	expect_signed(int, strxtos, "2a", 16, 42);
	return 0;
}

unitest_routine(strxto_fixed_unsigned)
{
	expect_unsigned(uint64_t, strxtou64, "18446744073709551615", 10,
			UINT64_MAX);
	expect_unsigned(uint32_t, strxtou32, "4294967295", 10, UINT32_MAX);
	expect_unsigned(uint16_t, strxtou16, "65535", 10, UINT16_MAX);
	expect_unsigned(uint8_t, strxtou8, "255", 10, UINT8_MAX);

	expect_error(uint64_t, strxtou64, "18446744073709551616", 10, ERANGE);
	expect_error(uint32_t, strxtou32, "4294967296", 10, ERANGE);
	expect_error(uint16_t, strxtou16, "65536", 10, ERANGE);
	expect_error(uint8_t, strxtou8, "256", 10, ERANGE);
	return 0;
}

unitest_routine(strxto_fixed_signed)
{
	expect_signed(int64_t, strxtos64, "9223372036854775807", 10, INT64_MAX);
	expect_signed(int64_t, strxtos64, "-9223372036854775808", 10,
		      INT64_MIN);
	expect_signed(int32_t, strxtos32, "2147483647", 10, INT32_MAX);
	expect_signed(int32_t, strxtos32, "-2147483648", 10, INT32_MIN);
	expect_signed(int16_t, strxtos16, "32767", 10, INT16_MAX);
	expect_signed(int16_t, strxtos16, "-32768", 10, INT16_MIN);
	expect_signed(int8_t, strxtos8, "127", 10, INT8_MAX);
	expect_signed(int8_t, strxtos8, "-128", 10, INT8_MIN);

	expect_error(int64_t, strxtos64, "9223372036854775808", 10, ERANGE);
	expect_error(int64_t, strxtos64, "-9223372036854775809", 10, ERANGE);
	expect_error(int32_t, strxtos32, "2147483648", 10, ERANGE);
	expect_error(int32_t, strxtos32, "-2147483649", 10, ERANGE);
	expect_error(int16_t, strxtos16, "32768", 10, ERANGE);
	expect_error(int16_t, strxtos16, "-32769", 10, ERANGE);
	expect_error(int8_t, strxtos8, "128", 10, ERANGE);
	expect_error(int8_t, strxtos8, "-129", 10, ERANGE);
	return 0;
}

unitest_end();
