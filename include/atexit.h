/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef ATEXIT_H
#define ATEXIT_H

typedef void (*atexit_routine_t)(void);

void atexit_push(atexit_routine_t fn);

atexit_routine_t atexit_pop(void);

void atexit_setup(void);

#endif /* ATEXIT_H */
