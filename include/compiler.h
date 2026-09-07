/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef COMPILER_H
#define COMPILER_H

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define BUG_ON(x) if (BUG_ON_EXPR(x))
#define BUG_ON_EXPR(x) (sizeof(struct { int:(-!!(x)); }) & 0)

#define type_is_same(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

#define type_is_signed(x) ((typeof(x))-1 < 0)

#define assert_same_type(a, b) BUG_ON_EXPR(!type_is_same(a, b))

#define assert_diff_type(a, b) BUG_ON_EXPR(type_is_same(a, b))

#define assert_array(x) BUG_ON_EXPR(type_is_same(x, &x[0]))

#define assert_pow2(x) BUG_ON_EXPR(!(x) || ((x) % 2) != 0)

#define assert_ascii(x) BUG_ON_EXPR(((unsigned char)x) & 0x80)

#ifdef CC_HAS_BUILTIN_ALIGN_UP
# define align_up(m, n) __builtin_align_up(m, n)
#else
# define align_up(m, n) (__align_up(m, n) + assert_pow2(n))
# define __align_up(m, n) (((m) + (n) - 1) & ~(uintmax_t)(n - 1))
#endif

#ifdef CC_HAS_BUILTIN_ALIGN_DOWN
# define align_down(m, n) __builtin_align_down(m, n)
#else
# define align_down(m, n) (__align_down(m, n) + assert_pow2(n))
# define __align_down(m, n) ((m) & ~(uintmax_t)(n - 1))
#endif

#define container_of(x, type, memb)				\
({								\
	BUG_ON(!type_is_same(*(x), void) &&			\
	       !type_is_same(*(x), ((type *)0)->memb));		\
	(type *)((void *)(x) - __builtin_offsetof(type, memb));	\
})

#define unreachable __builtin_unreachable

#define popcount __builtin_popcount

#define alignof __alignof__

#define trap __builtin_trap

#endif /* COMPILER_H */
