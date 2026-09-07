// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "size.h"
#include "strbuf.h"
#include "uniassert.h"
#include "unitest.h"

unitest_begin();

unitest_routine(sb_write_str_empty)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));
	size_t nr;

	nr = sb_write_str(&sb, "");
	uniassert_equal(sb.len, 0);
	uniassert_equal(sb.buf[0], 0);
	uniassert_equal(nr, 0);

	uniassert_strequal(sb.buf, "");
	return 0;
}

unitest_routine(sb_write_str_at_head)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));
	size_t nr;

	nr = sb_write_str(&sb, "miku");
	uniassert_equal(sb.len, 4);
	uniassert_equal(sb.buf[4], 0);
	uniassert_equal(nr, 4);

	nr = sb_write_str_at(&sb, 0, "39");
	uniassert_equal(sb.len, 2);
	uniassert_equal(sb.buf[2], 0);
	uniassert_equal(nr, 2);

	uniassert_strequal(sb.buf, "39");
	return 0;
}

unitest_routine(sb_write_str_at_mid)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));
	size_t nr;

	nr = sb_write_str(&sb, "HatsuneMiku");
	uniassert_equal(sb.len, 11);
	uniassert_equal(sb.buf[11], 0);
	uniassert_equal(nr, 11);

	nr = sb_write_str_at(&sb, 7, " Miku");
	uniassert_equal(sb.len, 12);
	uniassert_equal(sb.buf[12], 0);
	uniassert_equal(nr, 5);

	uniassert_strequal(sb.buf, "Hatsune Miku");
	return 0;
}

unitest_routine(sb_write_str_at_tail)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));
	size_t nr;

	nr = sb_write_str(&sb, "mi");
	uniassert_equal(sb.len, 2);
	uniassert_equal(sb.buf[2], 0);
	uniassert_equal(nr, 2);

	nr = sb_write_str_at(&sb, sb.len, "ku");
	uniassert_equal(sb.len, 4);
	uniassert_equal(sb.buf[4], 0);
	uniassert_equal(nr, 2);

	uniassert_strequal(sb.buf, "miku");
	return 0;
}

unitest_routine(sb_write_str_at_overflow)
{
	char buf1[2];
	char buf2[4];
	struct strbuf sb = SB_INIT_PREALLOC(buf1, sizeof(buf1));
	size_t nr;

	nr = sb_write_str(&sb, "39");
	uniassert_equal(sb.len, 0);
	uniassert_equal(nr, 0);

	sb.buf = buf2;
	sb.cap = sizeof(buf2);

	nr = sb_write_str(&sb, "39");
	uniassert_equal(sb.len, 2);
	uniassert_equal(sb.buf[2], 0);
	uniassert_equal(nr, 2);

	nr = sb_write_str(&sb, "39");
	uniassert_equal(sb.len, 2);
	uniassert_equal(sb.buf[2], 0);
	uniassert_equal(nr, 0);

	uniassert_strequal(sb.buf, "39");
	return 0;
}

unitest_routine(sb_writef_empty)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));
	size_t nr;

	nr = sb_writef(&sb, "%s", "");
	uniassert_equal(sb.len, 0);
	uniassert_equal(sb.buf[0], 0);
	uniassert_equal(nr, 0);

	uniassert_strequal(sb.buf, "");
	return 0;
}

unitest_routine(sb_writef_at_head)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));
	size_t nr;

	nr = sb_writef_at(&sb, 0, "%s", "miku");
	uniassert_equal(sb.len, 4);
	uniassert_equal(sb.buf[4], 0);
	uniassert_equal(nr, 4);

	nr = sb_writef_at(&sb, 0, "%d", 39);
	uniassert_equal(sb.len, 2);
	uniassert_equal(sb.buf[2], 0);
	uniassert_equal(nr, 2);

	uniassert_strequal(sb.buf, "39");
	return 0;
}

unitest_routine(sb_writef_at_mid)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));
	size_t nr;

	nr = sb_writef_at(&sb, 0, "%s%s", "Hatsune", "Miku");
	uniassert_equal(sb.len, 11);
	uniassert_equal(sb.buf[11], 0);
	uniassert_equal(nr, 11);

	nr = sb_writef_at(&sb, 7, " %s", "Miku");
	uniassert_equal(sb.len, 12);
	uniassert_equal(sb.buf[12], 0);
	uniassert_equal(nr, 5);

	uniassert_strequal(sb.buf, "Hatsune Miku");
	return 0;
}

unitest_routine(sb_writef_tail)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));
	size_t nr;

	nr = sb_writef_at(&sb, 0, "%s", "mi");
	uniassert_equal(sb.len, 2);
	uniassert_equal(sb.buf[2], 0);
	uniassert_equal(nr, 2);

	nr = sb_writef(&sb, "%s", "ku");
	uniassert_equal(sb.len, 4);
	uniassert_equal(sb.buf[4], 0);
	uniassert_equal(nr, 2);

	uniassert_strequal(sb.buf, "miku");
	return 0;
}

unitest_routine(sb_writef_at_overflow)
{
	char buf1[2];
	char buf2[4];
	struct strbuf sb = SB_INIT_PREALLOC(buf1, sizeof(buf1));
	size_t nr;

	nr = sb_writef_at(&sb, 0, "%d", 39);
	uniassert_equal(sb.len, 0);
	uniassert_equal(nr, 0);

	sb.buf = buf2;
	sb.cap = sizeof(buf2);

	nr = sb_writef_at(&sb, 0, "%d", 39);
	uniassert_equal(sb.len, 2);
	uniassert_equal(sb.buf[2], 0);
	uniassert_equal(nr, 2);

	nr = sb_writef_at(&sb, sb.len, "%d", 39);
	uniassert_equal(sb.len, 2);
	uniassert_equal(sb.buf[2], 0);
	uniassert_equal(nr, 0);

	uniassert_strequal(sb.buf, "39");
	return 0;
}

unitest_end();
