/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef REALLOCARRAY_H
#define REALLOCARRAY_H

#include <stddef.h>

#ifndef CC_HAS_REALLOCARRAY
void *reallocarray(void *ptr, size_t nmemb, size_t size);
#endif

#endif /* REALLOCARRAY_H */
