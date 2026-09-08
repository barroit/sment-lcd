// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdio.h>

const char *cmd_dump_all_help = "print the complete test dump";

int cmd_dump_all(int argc, const char **argv)
{
	(void)argc;
	(void)argv;

	puts("dump: all");
	return 0;
}
