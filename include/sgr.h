/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef SGR_H
#define SGR_H

#include "cpp.h"

/*
 * \033[<style>;<foreground>;<background>m
 * \033[<style>;<color>m
 * \033[<style|color>m
 *
 * Style			Foreground		Background
 * 0	Reset			30    Black		40	Black
 * 1	Bold/bright		31    Red		41	Red
 * 2	Faint			32    Green		42	Green
 * 3	Italic			33    Yellow		43	Yellow
 * 4	Underline		34    Blue		44	Blue
 * 5	Blink			35    Magenta		45	Magenta
 * 7	Inverse			36    Cyan		46	Cyan
 * 22	Normal intensity	37    White		47	White
 * 24	No underline		90    Bright Black	100	Bright Black
 * 25	No blink		91    Bright Red	101	Bright Red
 *				92    Bright Green	102	Bright Green
 *				93    Bright Yellow	103	Bright Yellow
 *				94    Bright Blue	104	Bright Blue
 *				95    Bright Magenta	105	Bright Magenta
 *				96    Bright Cyan	106	Bright Cyan
 *				97    Bright White	107	Bright White
 */

#define __sgr_begen "\033["
#define __sgr_end "m"
#define __sgr_sep ";"

#define __sgr(...) CALL(__sgr_, __VA_ARGS__)
#define __sgr_1(x) __sgr_begen #x __sgr_end
#define __sgr_2(x, y) __sgr_begen #x __sgr_sep #y __sgr_end
#define __sgr_3(x, y, z) __sgr_begen #x __sgr_sep #y __sgr_sep #z __sgr_end

#define SGR_RESET 0
#define SGR_BOLD  1

#define SGR_BLACK   30
#define SGR_RED     31
#define SGR_GREEN   32
#define SGR_YELLOW  33
#define SGR_BLUE    34
#define SGR_MAGENTA 35
#define SGR_CYAN    36
#define SGR_WHITE   37

#define SGR_BRIGHT_BLACK   90
#define SGR_BRIGHT_RED     91
#define SGR_BRIGHT_GREEN   92
#define SGR_BRIGHT_YELLOW  93
#define SGR_BRIGHT_BLUE    94
#define SGR_BRIGHT_MAGENTA 95
#define SGR_BRIGHT_CYAN    96
#define SGR_BRIGHT_WHITE   97

#define SGR_BG_BLACK   40
#define SGR_BG_RED     41
#define SGR_BG_GREEN   42
#define SGR_BG_YELLOW  43
#define SGR_BG_BLUE    44
#define SGR_BG_MAGENTA 45
#define SGR_BG_CYAN    46
#define SGR_BG_WHITE   47

#define H(x, ...) __sgr(__VA_ARGS__) x __sgr(SGR_RESET)

#endif /* SGR_H */
