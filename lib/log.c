// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "log.h"
#include "rio.h"
#include "sgr.h"
#include "size.h"
#include "strbuf.h"

static size_t format_line(char *buf, size_t cap, const char *prefix,
			  const char *hint, const char *fmt, va_list ap)
{
	struct strbuf sb = SB_INIT_PREALLOC(buf, cap - 1);

	if (prefix) {
		sb_write_str(&sb, prefix);
		sb_write_ch(&sb, ' ');
	}

	sb_vwritef(&sb, fmt, ap);

	if (hint) {
		sb_write_str(&sb, "; ");
		sb_write_str(&sb, hint);
	}

	sb.buf[sb.len++] = '\n';
	return sb.len;
}

void vlogf_fd(int fd, const char *prefix,
	      const char *hint, const char *fmt, va_list ap)
{
	char buf[SZ_2K];
	size_t len = format_line(buf, sizeof(buf), prefix, hint, fmt, ap);

	rwrite(fd, buf, len);
}

void logf_fd(int fd, const char *prefix, const char *hint, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vlogf_fd(fd, prefix, hint, fmt, ap);

	va_end(ap);
}

void vlogf_stream(FILE *stream, const char *prefix,
		  const char *hint, const char *fmt, va_list ap)
{
	char buf[SZ_2K];
	size_t len = format_line(buf, sizeof(buf), prefix, hint, fmt, ap);

	fwrite(buf, sizeof(*buf), len, stream);
}

void logf_stream(FILE *stream, const char *prefix,
		 const char *hint, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vlogf_stream(stream, prefix, hint, fmt, ap);

	va_end(ap);
}

int __warn(const char *hint, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vlogf_fd(STDERR_FILENO,
		 H("warn:", SGR_BOLD, SGR_YELLOW), hint, fmt, ap);

	va_end(ap);
	return 1;
}

int __error39(const char *hint, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vlogf_fd(STDERR_FILENO, H("error:", SGR_BOLD, SGR_RED), hint, fmt, ap);

	va_end(ap);
	return 1;
}

void __die(const char *hint, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vlogf_fd(STDERR_FILENO, H("fatal:", SGR_BOLD, SGR_RED), hint, fmt, ap);

	exit(128);
}

void __bug(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vlogf_fd(STDERR_FILENO, NULL, NULL, fmt, ap);

	abort();
}
