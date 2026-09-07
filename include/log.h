/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>

#include "attr.h"

void vlogf_fd(int fd, const char *prefix,
	    const char *hint, const char *fmt, va_list ap);

void logf_fd(int fd, const char *prefix,
	     const char *hint, const char *fmt, ...) __printf(4, 5);

void vlogf_stream(FILE *stream, const char *prefix,
		  const char *hint, const char *fmt, va_list ap);

void logf_stream(FILE *stream, const char *prefix,
		 const char *hint, const char *fmt, ...) __printf(4, 5);

#endif /* LOG_H */
