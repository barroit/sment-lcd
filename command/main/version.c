// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "libusb.h"

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

const char *cmd_version_help = "version";

int cmd_version(int argc, const char **argv)
{
	const struct libusb_version *libusb = libusb_get_version();

	printf("libusb %" PRIu16 ".%" PRIu16 ".%" PRIu16 "\n", libusb->major,
	        libusb->minor, libusb->micro);

	exit(0);
}
