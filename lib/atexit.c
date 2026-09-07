// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2024 Jiamu Sun <barroit@linux.com>
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdlib.h>

#include "atexit.h"
#include "attr.h"
#include "list.h"
#include "xalloc.h"

struct atexit_chain {
	atexit_routine_t fn;
	struct list_head list;
};

static LIST_HEAD(chain);

void atexit_push(atexit_routine_t fn)
{
	struct atexit_chain *c = xmalloc(sizeof(*c));

	c->fn = fn;
	list_add(&c->list, &chain);
}

atexit_routine_t atexit_pop(void)
{
	struct atexit_chain *c = list_first_entry(&chain,
						  struct atexit_chain, list);
	atexit_routine_t fn = c->fn;

	list_del(&c->list);
	free(c);
	return fn;
}

static void atexit_apply(void)
{
	while (!list_is_empty(&chain)) {
		atexit_routine_t fn = atexit_pop();

		fn();
	}
}

void atexit_setup(void)
{
	atexit(atexit_apply);
}
