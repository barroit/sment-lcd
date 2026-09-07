// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "log.h"
#include "rio.h"
#include "size.h"
#include "uniassert.h"
#include "unitest.h"

unitest_begin();

static int assert_stream_eq(FILE *stream, const char *expect)
{
	int fd = fileno(stream);
	char buf[SZ_4K];
	ssize_t nr;
	size_t len = strlen(expect);

	uniassert_equal_signed(lseek(fd, 0, SEEK_SET), 0);

	nr = rread(fd, buf, sizeof(buf) - 1);
	uniassert_equal_signed(nr, len);

	buf[nr] = 0;
	uniassert_strequal(buf, expect);

	return 0;
}

unitest_routine(logf_fd_empty)
{
	FILE *stream = tmpfile();
	int fd;

	uniassert_is(stream);
	fd = fileno(stream);

	logf_fd(fd, NULL, NULL, "%s", "");
	return assert_stream_eq(stream, "\n");
}

unitest_routine(logf_fd_fmt)
{
	FILE *stream = tmpfile();
	int fd;

	uniassert_is(stream);
	fd = fileno(stream);

	logf_fd(fd, NULL, NULL, "Hatsune %s", "Miku");
	return assert_stream_eq(stream, "Hatsune Miku\n");
}

unitest_routine(logf_fd_prefix)
{
	FILE *stream = tmpfile();
	int fd;

	uniassert_is(stream);
	fd = fileno(stream);

	logf_fd(fd, "error:", NULL, "Hatsune %s", "Miku");
	return assert_stream_eq(stream, "error: Hatsune Miku\n");
}

unitest_routine(logf_fd_hint)
{
	FILE *stream = tmpfile();
	int fd;

	uniassert_is(stream);
	fd = fileno(stream);

	logf_fd(fd, NULL, "try again", "Hatsune %s", "Miku");
	return assert_stream_eq(stream, "Hatsune Miku; try again\n");
}

unitest_routine(logf_fd_prefix_hint)
{
	FILE *stream = tmpfile();
	int fd;

	uniassert_is(stream);
	fd = fileno(stream);

	logf_fd(fd, "fatal:", "try again", "Hatsune %s", "Miku");
	return assert_stream_eq(stream, "fatal: Hatsune Miku; try again\n");
}

unitest_routine(logf_fd_overflow)
{
	FILE *stream = tmpfile();
	int fd;
	char expect[SZ_2K];
	char fill[SZ_2K];
	char msg[SZ_2K];

	uniassert_is(stream);
	fd = fileno(stream);

	memset(fill, '3', sizeof(fill));
	fill[sizeof(fill) - 1] = 0;

	memset(msg, 'm', sizeof(msg));
	msg[sizeof(msg) - 2] = 0;

	memset(expect, 'm', sizeof(expect));
	expect[sizeof(expect) - 2] = '\n';
	expect[sizeof(expect) - 1] = 0;

	logf_fd(fd, NULL, fill, "%s", msg);
	return assert_stream_eq(stream, expect);
}

unitest_routine(logf_fd_prefix_overflow)
{
	FILE *stream = tmpfile();
	int fd;
	char expect[SZ_2K];
	char fill[SZ_2K];
	char msg[SZ_2K];

	uniassert_is(stream);
	fd = fileno(stream);

	memset(fill, '3', sizeof(fill));
	fill[sizeof(fill) - 1] = 0;

	memset(msg, 'm', sizeof(msg));
	msg[sizeof(msg) - 4] = 0;

	memset(expect, 'm', sizeof(expect));
	expect[0] = 'x';
	expect[1] = ' ';
	expect[sizeof(expect) - 2] = '\n';
	expect[sizeof(expect) - 1] = 0;

	logf_fd(fd, "x", fill, "%s", msg);
	return assert_stream_eq(stream, expect);
}

unitest_end();
