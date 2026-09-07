// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2025 Jiamu Sun <barroit@linux.com>
 *
 * https://github.com/google/sanitizers/wiki/AddressSanitizerFlags
 */

const char *__asan_default_options(void);
const char *__ubsan_default_options(void);

#define SANITIZER_OPTIONS "abort_on_error=1:" \
			  "disable_coredump=0"

const char *__asan_default_options(void)
{
	return SANITIZER_OPTIONS;
}

const char *__ubsan_default_options(void)
{
	return SANITIZER_OPTIONS;
}
