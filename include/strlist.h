/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2024, 2025 Jiamu Sun <barroit@linux.com>
 * Copyright 2026 Jiamu Sun <39@barroit.sh> 
 *
 * The strlist relies heavily on flags. Invalid combinations are easy to create.
 * See assertions in lib/strlist.c for constraints.
 */

#ifndef STRLIST_H
#define STRLIST_H

#include <stdint.h>
#include <stddef.h>

#include "list.h"

struct strbuf;

struct strlist_item {
	union {
		struct strbuf *sb;
		const char *ref;
		char *cp;
	};

	struct list_head list;
};

struct strlist {
	struct list_head head;
	struct list_head idle;

	size_t items;

	uint64_t flags;
};

#define SL_USE_CP  (1u << 0) /* store a copy of string */
#define SL_USE_REF (1u << 1) /* store reference, no string allocation */
#define SL_USE_SB  (1u << 2) /* use strbuf as internal buffer, cached */
#define SL_RET_LEN (1u << 3) /* return the string length on sl_push_*() */
#define SL_POP_DUP (1u << 4) /* duplicate string on sl_pop() */

#define __sl_mode_mask (SL_USE_CP | SL_USE_REF | SL_USE_SB)
#define __sl_mode(f)   ((f) & __sl_mode_mask)

#define SL_INIT_CP(s) SL_INIT(s, SL_USE_CP | SL_RET_LEN)
#define SL_INIT(s, f) {				\
	.head  = LIST_HEAD_INIT(s.head),	\
	.idle  = LIST_HEAD_INIT(s.idle),	\
	.flags = f,				\
}

void sl_init(struct strlist *sl, uint64_t flags);

void sl_destroy(struct strlist *sl);

size_t sl_push(struct strlist *sl, const char *str);

size_t sl_push_back(struct strlist *sl, const char *str);

/*
 * Always free the returned pointer when SL_USE_CP is set.
 *
 * Don't keep returned pointer across later sl_push() or sl_push_back() calls
 * when SL_USE_SB is set and SL_POP_DUP is not set. These calls may invalidate
 * it.
 */
char *sl_pop(struct strlist *sl);

void sl_read_line(struct strlist *sl, const char *str, size_t wrap);

char **sl_to_argv(struct strlist *sl);

#endif /* STRLIST_H */
