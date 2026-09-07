/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2024, 2025 Jiamu Sun <barroit@linux.com>
 */

#ifndef FOREACH_H
#define FOREACH_H

#include "calc.h"

#define foreach_idx(idx, stop) \
	for (idx = 0; idx < stop; idx++)

/*
 * The maximum value of `start` is maxof(idx) - 1.
 */
#define foreach_idx_reverse(idx, start) \
	for (idx = start; idx != maxof(idx); idx--)

#define foreach_idx_from(idx, stop) \
	for (; idx < stop; idx++)

#endif /* FOREACH_H */
