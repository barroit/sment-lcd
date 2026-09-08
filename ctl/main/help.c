// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdio.h>

const char *cmd_main_help_help = "show the command-tree test commands";

int cmd_main_help(int argc, const char **argv)
{
	(void)argc;
	(void)argv;

	puts("try: smentlcdctl dump remote url");
	return 0;
}
