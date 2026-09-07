/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2024, 2025 Jiamu Sun <barroit@linux.com>
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef UNICODE_H
#define UNICODE_H

#include <stddef.h>

enum uc_mbctype {
	_UC_9CB,  /* continuation bytes */
	_UC_9A,   /* 1-byte */
	_UC_9B,   /* 2-byte */
	_UC_9C,   /* 3-byte */
	_UC_9D,   /* 4-byte */
};

extern unsigned int _uc_mbctype[];

void uc_force_utf8_ctype(void);

#define uc_ismbctype(c, t) (uc_mbctype(c) == t)
#define uc_mbctype(c) _uc_mbctype[(unsigned int)c]

#define uc_ismb1(c)  uc_ismbctype(c, _UC_9A)
#define uc_ismb2(c)  uc_ismbctype(c, _UC_9B)
#define uc_ismb3(c)  uc_ismbctype(c, _UC_9C)
#define uc_ismb4(c)  uc_ismbctype(c, _UC_9D)
#define uc_ismbcb(c) uc_ismbctype(c, _UC_9CB)

int uc_iseoc(wchar_t c);

int uc_iswide(wchar_t c);

size_t uc_mbslen(const char *s);

wchar_t uc_mbtowc(const char *seq);

#endif /* UNICODE_H */
