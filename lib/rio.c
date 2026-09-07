// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <errno.h>
#include <unistd.h>

#include "rio.h"

ssize_t rread(int fd, void *buf, size_t count)
{
	ssize_t nr;

	do {
		nr = read(fd, buf, count);
	} while (nr == -1 && errno == EINTR);

	return nr;
}

ssize_t rwrite(int fd, const void *buf, size_t count)
{
	ssize_t nr;

	do {
		nr = write(fd, buf, count);
	} while (nr == -1 && errno == EINTR);

	return nr;
}
