// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "err.h"
#include "log.h"
#include "sgr.h"

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

