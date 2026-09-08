// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdio.h>

const char *cmd_dump_remote_connect_help = "test the remote connection";

int cmd_dump_remote_connect(int argc, const char **argv)
{
	(void)argc;
	(void)argv;

	puts("remote: connected");
	return 0;
}
