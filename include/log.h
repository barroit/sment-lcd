/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef LOG_H
#define LOG_H

#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "attr.h"

extern char *strerror(int errnum);

#define warn(fmt, ...) __log_warn(NULL, fmt, ##__VA_ARGS__)
#define warn_errno(fmt, ...) warn_errno2(errno, fmt, ##__VA_ARGS__)
#define warn_errno2(e, fmt, ...) __log_warn(strerror(e), fmt, ##__VA_ARGS__)

#define error(fmt, ...) __log_error(NULL, fmt, ##__VA_ARGS__)
#define error_errno(fmt, ...) error_errno2(errno, fmt, ##__VA_ARGS__)
#define error_errno2(e, fmt, ...) __log_error(strerror(e), fmt, ##__VA_ARGS__)

#define die(fmt, ...) __log_die(NULL, fmt, ##__VA_ARGS__)
#define die_errno(fmt, ...) die_errno2(errno, fmt, ##__VA_ARGS__)
#define die_errno2(e, fmt, ...) __log_die(strerror(e), fmt, ##__VA_ARGS__)

#define bug(fmt, ...)							\
	__log_bug("%s:%d,%s(): " fmt, __FILE__, __LINE__, __func__,	\
		  ##__VA_ARGS__)

int __log_warn(const char *hint, const char *fmt, ...)  __printf(2, 3);

int __log_error(const char *hint, const char *fmt, ...) __printf(2, 3);

void __log_die(const char *hint, const char *fmt, ...) __printf(2, 3)
						       __noreturn;

void __log_bug(const char *fmt, ...) __printf(1, 2) __noreturn;

void log_vwritef(int fd, const char *prefix, const char *hint,
		 const char *fmt, va_list ap);

void log_writef(int fd, const char *prefix, const char *hint,
		const char *fmt, ...) __printf(4, 5);

void log_vprintf(FILE *stream, const char *prefix, const char *hint,
		 const char *fmt, va_list ap);

void log_printf(FILE *stream, const char *prefix, const char *hint,
		const char *fmt, ...) __printf(4, 5);

#endif /* LOG_H */
