// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stddef.h>

#include "strutil.h"

const char *strskip(const char *s1, const char *s2)
{
	do {
		if (!s2[0])
			return (char *)s1;
	} while (*s1++ == *s2++);

	return NULL;
}

int strskip2(const char *s1, const char *s2, const char **__res)
{
	const char *res = strskip(s1, s2);

	if (res == NULL)
		return -1;

	*__res = res;
	return 0;
}
