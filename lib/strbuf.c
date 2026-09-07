// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "size.h"
#include "strbuf.h"
#include "xalloc.h"

void sb_init(struct strbuf *sb, uint64_t mode)
{
	memset(sb, 0, sizeof(*sb));

	sb->mode = mode;
}

void sb_destroy(struct strbuf *sb)
{
	free(sb->buf);

	sb->buf = NULL;
}

void sb_reinit(struct strbuf *sb, uint64_t mode)
{
	sb_destroy(sb);
	memset(sb, 0, sizeof(*sb));

	sb->mode = mode;
}

void sb_chop(struct strbuf *sb, size_t len)
{
	sb->len -= len;
	sb->buf[sb->len] = 0;
}

void sb_trunc(struct strbuf *sb, size_t len)
{
	sb->len = len;
	sb->buf[len] = 0;
}

size_t sb_write_ch_at(struct strbuf *sb, size_t pos, char c)
{
	size_t new = pos + 1;

	assert(pos <= sb->len);

	if (new + 1 > sb->cap) {
		if (sb->mode & SB_PREALLOC)
			return 0;
		else
			XREALLOCBUF(sb->buf, new + 1, sb->cap);
	}

	sb->buf[pos] = c;
	sb->buf[pos + 1] = 0;

	sb->len = new;
	return 1;
}

size_t sb_write_str_at(struct strbuf *sb, size_t pos, const char *s)
{
	size_t len = strlen(s);
	size_t new = pos + len;

	assert(pos <= sb->len);

	if (new + 1 > sb->cap) {
		if (sb->mode & SB_PREALLOC)
			return 0;
		else
			XREALLOCBUF(sb->buf, new + 1, sb->cap);
	}

	memcpy(&sb->buf[pos], s, len + 1);

	sb->len = new;
	return len;
}

size_t sb_vwritef_at(struct strbuf *sb, size_t pos, const char *fmt, va_list ap)
{
	va_list cp;
	int nr;
	size_t new;

	assert(pos <= sb->len);
	va_copy(cp, ap);

	nr = vsnprintf(NULL, 0, fmt, cp);
	assert(nr >= 0);
	new = pos + nr;
	va_end(cp);

	if (new + 1 > sb->cap) {
		if (sb->mode & SB_PREALLOC)
			return 0;
		else
			XREALLOCBUF(sb->buf, new + 1, sb->cap);
	}

	nr = vsnprintf(&sb->buf[pos], nr + 1, fmt, ap);
	assert(nr >= 0);

	sb->len = new;
	return nr;
}

size_t sb_writef_at(struct strbuf *sb, size_t pos, const char *fmt, ...)
{
	va_list ap;
	size_t nr;

	va_start(ap, fmt);
	nr = sb_vwritef_at(sb, pos, fmt, ap);

	va_end(ap);
	return nr;
}
