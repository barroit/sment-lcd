// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <errno.h>
#include <stdlib.h>

#include "calc.h"
#include "patch/reallocarray.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (!mult_is_overflow(nmemb, size))
		return realloc(ptr, nmemb * size);

	errno = ERANGE;
	return NULL;
}
