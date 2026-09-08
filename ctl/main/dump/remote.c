// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "parse_argv.h"

const char *cmd_dump_remote_help = "inspect a remote endpoint";

static const char *usage[] = {
	"smentlcdctl dump remote <command> [<args>]",
	NULL,
};

int cmd_remote(int argc, const char **argv);

int cmd_dump_remote(int argc, const char **argv)
{
	pa_command_fn cmd;
	struct pa_opt opts[] = {
		CMD_DUMP_REMOTE_CMDS(&cmd),
		PA_OPT_END(),
	};

	argc = pa_parse_args(argc, argv, opts, usage, 0);
	return cmd(argc, argv);
}

int cmd_remote(int argc, const char **argv)
{
	return cmd_dump_remote(argc, argv);
}
