// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "size.h"
#include "strbuf.h"
#include "uniassert.h"
#include "unitest.h"

unitest_begin();

unitest_routine(sb_chop_tail)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));

	sb_write_str(&sb, "Hatsune Miku");
	sb_chop(&sb, 5);

	uniassert_equal(sb.len, 7);
	uniassert_equal(sb.buf[7], 0);
	uniassert_strequal(sb.buf, "Hatsune");
	return 0;
}

unitest_routine(sb_chop_zero)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));

	sb_write_str(&sb, "miku");
	sb_chop(&sb, 0);

	uniassert_equal(sb.len, 4);
	uniassert_equal(sb.buf[4], 0);
	uniassert_strequal(sb.buf, "miku");
	return 0;
}

unitest_routine(sb_chop_all)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));

	sb_write_str(&sb, "39");
	sb_chop(&sb, sb.len);

	uniassert_equal(sb.len, 0);
	uniassert_equal(sb.buf[0], 0);
	uniassert_strequal(sb.buf, "");
	return 0;
}

unitest_routine(sb_trunc_mid)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));

	sb_write_str(&sb, "Hatsune Miku");
	sb_trunc(&sb, 7);

	uniassert_equal(sb.len, 7);
	uniassert_equal(sb.buf[7], 0);
	uniassert_strequal(sb.buf, "Hatsune");
	return 0;
}

unitest_routine(sb_trunc_zero)
{
	char buf[SZ_4K];
	struct strbuf sb = SB_INIT_PREALLOC(buf, sizeof(buf));

	sb_write_str(&sb, "miku");
	sb_trunc(&sb, 0);

	uniassert_equal(sb.len, 0);
	uniassert_equal(sb.buf[0], 0);
	uniassert_strequal(sb.buf, "");
	return 0;
}

unitest_end();
