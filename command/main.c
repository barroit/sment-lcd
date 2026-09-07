// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "atexit.h"
#include "parse_argv.h"
#include "unicode.h"

#include <stdio.h>

static const char *usage[] = {
	"test",
	NULL,
};

int cmd_main(int argc, const char **argv)
{
	pa_command_fn cmd;
	const char *test = "0";
	struct pa_opt opts[] = {
		PA_OPT_STRING("test1", 's', &test, "test"),
		PA_OPT_STRING("test2", 'c', &test, "test"),
		CMD_MAIN_CMDS(&cmd),
		PA_OPT_END(),
	};

	atexit_setup();
	uc_force_utf8_ctype();

	argc = pa_parse_args(argc, argv, opts, usage, 0);
	cmd(argc, argv);
	return 0;
}
