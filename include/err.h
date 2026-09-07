/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef ERR_H
#define ERR_H

#include <errno.h>
#include <stddef.h>

#include "attr.h"

extern char *strerror(int errnum);

#define warn(fmt, ...) __warn(NULL, fmt, ##__VA_ARGS__)
#define warn_errno(fmt, ...) __warn(strerror(errno), fmt, ##__VA_ARGS__)

#define error(fmt, ...) __error39(NULL, fmt, ##__VA_ARGS__)
#define error_errno(fmt, ...) __error39(strerror(errno), fmt, ##__VA_ARGS__)

#define die(fmt, ...) __die(NULL, fmt, ##__VA_ARGS__)
#define die_errno(fmt, ...) __die(strerror(errno), fmt, ##__VA_ARGS__)

#define bug(fmt, ...) \
	__bug("%s:%d,%s(): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

int __warn(const char *hint, const char *fmt, ...)  __printf(2, 3);

/*
 * Don't use __error(), some platforms define that.
 */
int __error39(const char *hint, const char *fmt, ...) __printf(2, 3);

void __die(const char *hint, const char *fmt, ...) __printf(2, 3) __noreturn;

void __bug(const char *fmt, ...) __printf(1, 2) __noreturn;

#endif /* ERR_H */
