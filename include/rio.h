/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef RIO_H
#define RIO_H

#include <sys/types.h>

/*
 * read(2) with retry on interruption support.
 */
ssize_t rread(int fd, void *buf, size_t count);

/*
 * write(2) with retry on interruption support.
 */
ssize_t rwrite(int fd, const void *buf, size_t count);

#endif /* RIO_H */
