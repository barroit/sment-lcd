// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdlib.h>

#include "strlist.h"
#include "uniassert.h"
#include "unitest.h"

unitest_begin();

unitest_routine(sl_init_default)
{
	struct strlist sl;
	char *str;
	size_t nr;

	sl_init(&sl, 0);

	nr = sl_push(&sl, "miku");
	uniassert_equal(nr, (size_t)-1);
	uniassert_equal(sl.items, 1);

	str = sl_pop(&sl);
	uniassert_strequal(str, "miku");
	uniassert_equal(sl.items, 0);

	free(str);
	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_push)
{
	struct strlist sl;
	char *str;

	sl_init(&sl, SL_USE_CP | SL_RET_LEN);

	uniassert_equal(sl_push(&sl, "miku"), 4);
	uniassert_equal(sl_push(&sl, "rin"), 3);
	uniassert_equal(sl.items, 2);

	str = sl_pop(&sl);
	uniassert_strequal(str, "rin");
	free(str);

	str = sl_pop(&sl);
	uniassert_strequal(str, "miku");
	free(str);

	uniassert_not(sl_pop(&sl));
	uniassert_equal(sl.items, 0);

	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_push_back)
{
	struct strlist sl;
	char *str;

	sl_init(&sl, SL_USE_CP | SL_RET_LEN);

	uniassert_equal(sl_push_back(&sl, "miku"), 4);
	uniassert_equal(sl_push_back(&sl, "rin"), 3);
	uniassert_equal(sl.items, 2);

	str = sl_pop(&sl);
	uniassert_strequal(str, "miku");
	free(str);

	str = sl_pop(&sl);
	uniassert_strequal(str, "rin");
	free(str);

	uniassert_not(sl_pop(&sl));
	uniassert_equal(sl.items, 0);

	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_use_ref)
{
	struct strlist sl;
	const char miku[] = "miku";
	const char rin[] = "rin";
	char *str;

	sl_init(&sl, SL_USE_REF | SL_RET_LEN);

	uniassert_equal(sl_push_back(&sl, miku), 4);
	uniassert_equal(sl_push_back(&sl, rin), 3);

	str = sl_pop(&sl);
	uniassert_equal(str, miku);
	uniassert_strequal(str, "miku");

	str = sl_pop(&sl);
	uniassert_equal(str, rin);
	uniassert_strequal(str, "rin");

	uniassert_equal(sl.items, 0);

	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_use_ref_pop_dup)
{
	struct strlist sl;
	const char miku[] = "miku";
	char *str;

	sl_init(&sl, SL_USE_REF | SL_POP_DUP);
	sl_push_back(&sl, miku);

	str = sl_pop(&sl);
	uniassert_not(str == miku);
	uniassert_strequal(str, "miku");
	uniassert_equal(sl.items, 0);

	free(str);
	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_use_sb)
{
	struct strlist sl;
	char *str;

	sl_init(&sl, SL_USE_SB | SL_RET_LEN);

	uniassert_equal(sl_push_back(&sl, "miku"), 4);
	str = sl_pop(&sl);
	uniassert_strequal(str, "miku");

	uniassert_equal(sl_push_back(&sl, "rin"), 3);
	str = sl_pop(&sl);
	uniassert_strequal(str, "rin");
	uniassert_equal(sl.items, 0);

	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_use_sb_pop_dup)
{
	struct strlist sl;
	char *str;

	sl_init(&sl, SL_USE_SB | SL_POP_DUP);
	sl_push_back(&sl, "miku");

	str = sl_pop(&sl);
	uniassert_strequal(str, "miku");
	uniassert_equal(sl.items, 0);

	free(str);
	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_read_line_plain)
{
	struct strlist sl;
	char *str;

	sl_init(&sl, SL_USE_CP);
	sl_read_line(&sl, "Hatsune Miku", 80);

	uniassert_equal(sl.items, 1);

	str = sl_pop(&sl);
	uniassert_strequal(str, "Hatsune Miku");
	free(str);

	uniassert_not(sl_pop(&sl));
	uniassert_equal(sl.items, 0);

	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_read_line_wrap_space)
{
	struct strlist sl;
	char *str;

	sl_init(&sl, SL_USE_CP);
	sl_read_line(&sl, "one two three", 7);

	uniassert_equal(sl.items, 2);

	str = sl_pop(&sl);
	uniassert_strequal(str, "one two");
	free(str);

	str = sl_pop(&sl);
	uniassert_strequal(str, "three");
	free(str);

	uniassert_not(sl_pop(&sl));
	uniassert_equal(sl.items, 0);

	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_read_line_wrap_eoc)
{
	struct strlist sl;
	char *str;

	sl_init(&sl, SL_USE_CP);
	sl_read_line(&sl, "one.two", 4);

	uniassert_equal(sl.items, 2);

	str = sl_pop(&sl);
	uniassert_strequal(str, "one.");
	free(str);

	str = sl_pop(&sl);
	uniassert_strequal(str, "two");
	free(str);

	uniassert_not(sl_pop(&sl));
	uniassert_equal(sl.items, 0);

	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_read_line_wrap_utf8)
{
	const char text[] = {
		'a', 'a',
		'\xef', '\xbc', '\x81',
		'b', 'b',
		0,
	};
	const char expect[] = {
		'a', 'a',
		'\xef', '\xbc', '\x81',
		0,
	};
	struct strlist sl;
	char *str;

	sl_init(&sl, SL_USE_CP);
	sl_read_line(&sl, text, 4);

	uniassert_equal(sl.items, 2);

	str = sl_pop(&sl);
	uniassert_strequal(str, expect);
	free(str);

	str = sl_pop(&sl);
	uniassert_strequal(str, "bb");
	free(str);

	uniassert_not(sl_pop(&sl));
	uniassert_equal(sl.items, 0);

	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_to_argv_cp)
{
	struct strlist sl;
	char **argv;

	sl_init(&sl, SL_USE_CP);
	sl_push_back(&sl, "miku");
	sl_push_back(&sl, "rin");

	argv = sl_to_argv(&sl);
	uniassert_strequal(argv[0], "miku");
	uniassert_strequal(argv[1], "rin");
	uniassert_not(argv[2]);
	uniassert_equal(sl.items, 0);

	free(argv[0]);
	free(argv[1]);
	free(argv);

	sl_destroy(&sl);
	return 0;
}

unitest_routine(sl_to_argv_ref)
{
	struct strlist sl;
	const char miku[] = "miku";
	const char rin[] = "rin";
	char **argv;

	sl_init(&sl, SL_USE_REF);
	sl_push_back(&sl, miku);
	sl_push_back(&sl, rin);

	argv = sl_to_argv(&sl);
	uniassert_equal(argv[0], miku);
	uniassert_equal(argv[1], rin);
	uniassert_not(argv[2]);
	uniassert_equal(sl.items, 0);

	free(argv);
	sl_destroy(&sl);
	return 0;
}

unitest_end();
