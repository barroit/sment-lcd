// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "parse_argv.h"

const char *cmd_main_dump_help = "dump test data";

static const char *usage[] = {
	"smentlcdctl dump <command> [<args>]",
	NULL,
};

int cmd_dump(int argc, const char **argv)
{
	pa_command_fn cmd;
	struct pa_opt opts[] = {
		CMD_DUMP_CMDS(&cmd),
		PA_OPT_END(),
	};

	argc = pa_parse_args(argc, argv, opts, usage, 0);
	return cmd(argc, argv);
}

int cmd_main_dump(int argc, const char **argv)
{
	return cmd_dump(argc, argv);
}
