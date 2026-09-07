/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef ATTR_H
#define ATTR_H

/*
 * optimization & inlining
 */

#undef __always_inline
#define __always_inline inline __attribute__((__always_inline__))

#undef __cold
#define __cold __attribute__((__cold__))

/*
 * function behavior & semantics
 */

#define __noreturn __attribute__((__noreturn__))

#undef __pure
#define __pure __attribute__((__pure__))

#define __malloc __attribute__((__malloc__))

#define __cleanup(x) __attribute__((__cleanup__(x)))

/*
 * static analysis & diagnostics
 */

#define __printf(fmt, va) __attribute__((__format__(__printf__, fmt, va)))

#define __warn_unused_result __attribute__((__warn_unused_result__))

#if __has_attribute(__access__)
# define __read_only(...) \
	 __attribute__((__access__(__read_only__, __VA_ARGS__)))
#else
# define __read_only(...)
#endif

/*
 * usage & visibility
 */

#undef __used
#define __used __attribute__((__used__))

#define __maybe_unused __attribute__((__unused__))

/*
 * linker & symbol control
 */

#define __section(x) __attribute__((__section__(x)))

#define __constructor __attribute__((__constructor__))

#undef __weak
#define __weak __attribute__((weak))

#define __no_asan __attribute__((no_sanitize("address")))

#endif /* ATTR_H */
