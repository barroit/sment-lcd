/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef STRCHRNUL_H
#define STRCHRNUL_H

#ifndef CC_HAS_STRCHRNUL
char *strchrnul(const char *s, int c);
#endif

#endif /* STRCHRNUL_H */
