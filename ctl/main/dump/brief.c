// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdio.h>

const char *cmd_dump_brief_help = "print the brief test dump";

int cmd_dump_brief(int argc, const char **argv)
{
	(void)argc;
	(void)argv;

	puts("dump: brief");
	return 0;
}
