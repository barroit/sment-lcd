// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdio.h>

const char *cmd_main_version_help = "version";

int cmd_main_version(int argc, const char **argv)
{
	(void)argc;
	(void)argv;

	puts("smentlcdctl test version");
	return 0;
}
