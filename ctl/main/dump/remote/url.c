// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdio.h>

const char *cmd_dump_remote_url_help = "print the test remote URL";

int cmd_dump_remote_url(int argc, const char **argv)
{
	(void)argc;
	(void)argv;

	puts("remote: https://example.invalid/");
	return 0;
}
