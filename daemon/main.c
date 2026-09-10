// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "compiler.h"
#include "parse_argv.h"

static const char *usage[] = {
	"smentlcd <command> [<args>]",
	NULL,
};

int cmd_main(int argc, const char **argv)
{
	pa_command_fn cmd;
	struct pa_opt opts[] = {
		CMD_MAIN_CMDS(&cmd),
		PA_OPT_END(),
	};

	argc = pa_parse_args(argc, argv, opts, usage, 0);
	cmd(argc, argv);

	cc_trap();
}
