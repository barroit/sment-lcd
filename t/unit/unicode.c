// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "uniassert.h"
#include "unicode.h"
#include "unitest.h"

unitest_begin();

unitest_routine(uc_ismb1)
{
	unsigned int c;

	for (c = 0x00; c <= 0x7f; c++) {
		uniassert_is(uc_ismb1(c));
		uniassert_not(uc_ismbcb(c));
		uniassert_not(uc_ismb2(c));
		uniassert_not(uc_ismb3(c));
		uniassert_not(uc_ismb4(c));
	}

	return 0;
}

unitest_routine(uc_ismbcb)
{
	unsigned int c;

	for (c = 0x80; c <= 0xbf; c++) {
		uniassert_not(uc_ismb1(c));
		uniassert_is(uc_ismbcb(c));
		uniassert_not(uc_ismb2(c));
		uniassert_not(uc_ismb3(c));
		uniassert_not(uc_ismb4(c));
	}

	return 0;
}

unitest_routine(uc_ismb2)
{
	unsigned int c;

	for (c = 0xc0; c <= 0xdf; c++) {
		uniassert_not(uc_ismb1(c));
		uniassert_not(uc_ismbcb(c));
		uniassert_is(uc_ismb2(c));
		uniassert_not(uc_ismb3(c));
		uniassert_not(uc_ismb4(c));
	}

	return 0;
}

unitest_routine(uc_ismb3)
{
	unsigned int c;

	for (c = 0xe0; c <= 0xef; c++) {
		uniassert_not(uc_ismb1(c));
		uniassert_not(uc_ismbcb(c));
		uniassert_not(uc_ismb2(c));
		uniassert_is(uc_ismb3(c));
		uniassert_not(uc_ismb4(c));
	}

	return 0;
}

unitest_routine(uc_ismb4)
{
	unsigned int c;

	for (c = 0xf0; c <= 0xf7; c++) {
		uniassert_not(uc_ismb1(c));
		uniassert_not(uc_ismbcb(c));
		uniassert_not(uc_ismb2(c));
		uniassert_not(uc_ismb3(c));
		uniassert_is(uc_ismb4(c));
	}

	return 0;
}

unitest_routine(uc_ismb_invalid)
{
	unsigned int c;

	for (c = 0xf8; c <= 0xff; c++) {
		uniassert_not(uc_ismb1(c));
		uniassert_not(uc_ismbcb(c));
		uniassert_not(uc_ismb2(c));
		uniassert_not(uc_ismb3(c));
		uniassert_not(uc_ismb4(c));
	}

	return 0;
}

unitest_routine(uc_iseoc_punct)
{
	const wchar_t punct[] = {
		0x0021,
		0x002c,
		0x002e,
		0x003f,
		0x2025,
		0x2026,
		0x3001,
		0x3002,
		0xff01,
		0xff0c,
		0xff0e,
		0xff1f,
	};
	size_t idx;

	for (idx = 0; idx < sizeof(punct) / sizeof(punct[0]); idx++)
		uniassert_is(uc_iseoc(punct[idx]));

	return 0;
}

unitest_routine(uc_iseoc_non_punct)
{
	const wchar_t chars[] = {
		0x0020,
		0x003a,
		0x2024,
		0x2027,
		0x3000,
		0x3003,
		0xff02,
		0xff1e,
		0xff20,
	};
	size_t idx;

	for (idx = 0; idx < sizeof(chars) / sizeof(chars[0]); idx++)
		uniassert_not(uc_iseoc(chars[idx]));

	return 0;
}

unitest_routine(uc_iswide)
{
	const wchar_t chars[] = {
		0x1100,
		0x115f,
		0x231a,
		0x3041,
		0x3096,
		0xac00,
		0xd7a3,
		0xff01,
		0xff60,
	};
	size_t idx;

	for (idx = 0; idx < sizeof(chars) / sizeof(chars[0]); idx++)
		uniassert_is(uc_iswide(chars[idx]));

	return 0;
}

unitest_routine(uc_iswide_narrow)
{
	const wchar_t chars[] = {
		0x0021,
		0x10ff,
		0x1160,
		0x231c,
		0x2e9a,
		0x3040,
		0x3097,
		0xa48d,
		0xd7a4,
		0xff61,
	};
	size_t idx;

	for (idx = 0; idx < sizeof(chars) / sizeof(chars[0]); idx++)
		uniassert_not(uc_iswide(chars[idx]));

	return 0;
}

unitest_routine(uc_mbslen_empty)
{
	uniassert_equal(uc_mbslen(""), 0);
	return 0;
}

unitest_routine(uc_mbslen_utf8)
{
	const char s[] = {
		'A',
		'\xc2', '\xa2',
		'\xe3', '\x81', '\xbf',
		'\xf0', '\x9f', '\x98', '\x80',
		0,
	};

	uniassert_equal(uc_mbslen(s), 4);
	return 0;
}

unitest_routine(uc_mbtowc_ascii)
{
	uniassert_equal(uc_mbtowc("A"), 0x41);
	return 0;
}

unitest_routine(uc_mbtowc_2byte)
{
	const char seq[] = { '\xc2', '\xa2', 0 };

	uniassert_equal(uc_mbtowc(seq), 0xa2);
	return 0;
}

unitest_routine(uc_mbtowc_3byte)
{
	const char seq[] = { '\xe3', '\x81', '\xbf', 0 };

	uniassert_equal(uc_mbtowc(seq), 0x307f);
	return 0;
}

unitest_routine(uc_mbtowc_4byte)
{
	const char seq[] = { '\xf0', '\x9f', '\x98', '\x80', 0 };

	uniassert_equal(uc_mbtowc(seq), 0x1f600);
	return 0;
}

unitest_end();
