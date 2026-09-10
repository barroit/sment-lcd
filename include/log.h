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

#define warn(fmt, ...) __warn(NULL, fmt, ##__VA_ARGS__)
#define warn_errno(fmt, ...) warn_errno2(errno, fmt, ##__VA_ARGS__)
#define warn_errno2(e, fmt, ...) __warn(strerror(e), fmt, ##__VA_ARGS__)

#define error(fmt, ...) __error39(NULL, fmt, ##__VA_ARGS__)
#define error_errno(fmt, ...) error_errno2(errno, fmt, ##__VA_ARGS__)
#define error_errno2(e, fmt, ...) __error39(strerror(e), fmt, ##__VA_ARGS__)

#define die(fmt, ...) __die(NULL, fmt, ##__VA_ARGS__)
#define die_errno(fmt, ...) die_errno2(errno, fmt, ##__VA_ARGS__)
#define die_errno2(e, fmt, ...) __die(strerror(e), fmt, ##__VA_ARGS__)

#define bug(fmt, ...) \
	__bug("%s:%d,%s(): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

int __warn(const char *hint, const char *fmt, ...)  __printf(2, 3);

/*
 * Don't use __error(), some platforms define that.
 */
int __error39(const char *hint, const char *fmt, ...) __printf(2, 3);

void __die(const char *hint, const char *fmt, ...) __printf(2, 3) __noreturn;

void __bug(const char *fmt, ...) __printf(1, 2) __noreturn;

void vlogf_fd(int fd, const char *prefix,
	     const char *hint, const char *fmt, va_list ap);

void logf_fd(int fd, const char *prefix,
	     const char *hint, const char *fmt, ...) __printf(4, 5);

void vlogf_stream(FILE *stream, const char *prefix,
		  const char *hint, const char *fmt, va_list ap);

void logf_stream(FILE *stream, const char *prefix,
		 const char *hint, const char *fmt, ...) __printf(4, 5);

#endif /* LOG_H */
