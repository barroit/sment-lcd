/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2024 Jiamu Sun <barroit@linux.com>
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef STRTOX_H
#define STRTOX_H

#include <stdint.h>

int strxtoull(const char *str, int base, unsigned long long *res);
int strxtoul(const char *str, int base, unsigned long *res);
int strxtou(const char *str, int base, unsigned int *res);

int strxtoll(const char *str, int base, long long *res);
int strxtol(const char *str, int base, long *res);
int strxtos(const char *str, int base, int *res);

int strxtou64(const char *str, int base, uint64_t *res);
int strxtou32(const char *str, int base, uint32_t *res);
int strxtou16(const char *str, int base, uint16_t *res);
int strxtou8(const char *str, int base, uint8_t *res);

int strxtos64(const char *str, int base, int64_t *res);
int strxtos32(const char *str, int base, int32_t *res);
int strxtos16(const char *str, int base, int16_t *res);
int strxtos8(const char *str, int base, int8_t *res);

#endif /* STRTOX_H */
