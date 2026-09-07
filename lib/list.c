// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2024 Jiamu Sun <barroit@linux.com>
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "err.h"
#include "list.h"

void __list_die_add(const struct list_head *new,
		    const struct list_head *prev,
		    const struct list_head *next)
{
	if (new == prev || new == next)
		bug("list_add double add; new=%px, prev=%px, next=%px",
		    new, prev, next);
	else if (prev == NULL || next == NULL)
		bug("list_add corruption; prev=%px, next=%px", prev, next);
	else if (next->prev != prev)
		bug("list_add corruption; next->prev should be prev (%px), but was %px",
		    prev, next->prev);
	else if (prev->next != next)
		bug("list_add corruption; prev->next should be next (%px), but was %px",
		    next, prev->next);

	unreachable();
}

void __list_die_del(const struct list_head *entry)
{
	struct list_head *prev = entry->prev;
	struct list_head *next = entry->next;

	if (prev == NULL || next == NULL ||
	    next == POISON_ADDR_1 || prev == POISON_ADDR_2)
		bug("list_del corruption; prev=%px, next=%px", prev, next);
	else if (next->prev != prev)
		bug("list_del corruption; next->prev should be prev (%px), but was %px",
		    prev, next->prev);
	else if (prev->next != next)
		bug("list_del corruption; prev->next should be next (%px), but was %px",
		    next, prev->next);

	unreachable();
}
