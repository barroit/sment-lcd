// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdio.h>

const char *cmd_main_tmp_help = "run the daemon command-tree test";

int cmd_main_tmp(int argc, const char **argv)
{
	(void)argc;
	(void)argv;

	puts("daemon: tmp");
	return 0;
}
