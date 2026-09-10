// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdlib.h>

#include "ipc.h"

#include <stdio.h>

const char *cmd_main_start_help = "start the daemon process";

static void adjust_brightness(struct ipc_response *res, int64_t val)
{
	if (val < 0 || val > 100) {
		res->type = IPC_RES_ERROR;
		res->error = "brightness out of range (accept: 0..100)";
		return;
	}
}

static void exec_req(struct ipc_request *req, struct ipc_response *res)
{
	switch (req->type) {
	case IPC_REQ_FRAME:
		break;
	case IPC_REQ_BRIGHTNESS:
		adjust_brightness(res, req->brightness);
		break;
	case IPC_REQ_CLEAR:
		break;
	case IPC_REQ_POWER:
		break;
	case IPC_REQ_STATUS:
	}
}

int cmd_main_start(int argc, const char **argv)
{
	struct ipc_ctx *ctx;

	ipc_init(&ctx);

	ipc_bind_exec_req(ctx, exec_req);

	ipc_listen(ctx);

	abort();
}
