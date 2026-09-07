// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "patch/strchrnul.h"

char *strchrnul(const char *s, int c)
{
	while(*s && *s != c)
		s++;

	return (char *)s;
}
