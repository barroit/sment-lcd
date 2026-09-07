/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 * Copyright 2024 Jiamu Sun <barroit@linux.com>
 *
 * For details on how memory barriers work, take a look at the linux kernel's
 * Documentation/memory-barriers.txt. Although it's related to the kernel, the
 * essential mechanisms are interoperable.
 */

#ifndef BARRIER_H
#define BARRIER_H

#define READ_ONCE(x)       __atomic_load_n(&(x), __ATOMIC_RELAXED)
#define WRITE_ONCE(x, val) __atomic_store_n(&(x), val, __ATOMIC_RELAXED)

#endif /* BARRIER_H */
