// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#include "compiler.h"
#include "strbuf.h"
#include "strlist.h"
#include "unicode.h"
#include "xalloc.h"

#define WORD_AVG_LEN 8

void sl_init(struct strlist *sl, uint64_t flags)
{
	if (popcount(__sl_mode(flags)) == 0)
		flags |= SL_USE_CP;

	assert(popcount(__sl_mode(flags)) == 1);

	sl->flags = flags;
	list_head_init(&sl->head);
	list_head_init(&sl->idle);

	sl->items = 0;
}

static void __sl_destroy(struct strlist *sl, struct list_head *head)
{
	struct strlist_item *item, *tmp;

	list_foreach_entry_safe(item, tmp, head, list) {
		switch (__sl_mode(sl->flags)) {
		case SL_USE_CP:
			free(item->cp);
			break;
		case SL_USE_SB:
			sb_destroy(item->sb);
			free(item->sb);
			break;
		case SL_USE_REF:
			free(item);
		}
	}
}

void sl_destroy(struct strlist *sl)
{
	__sl_destroy(sl, &sl->head);

	if (sl->flags & (SL_USE_SB | SL_USE_REF))
		__sl_destroy(sl, &sl->idle);
}

static struct strlist_item *alloc_item_cp(const char *str, size_t *__len)
{
	struct strlist_item *item;
	size_t str_len = strlen(str);
	size_t data_len = align_up(str_len + 1, alignof(*item));
	char *buf = xmalloc(data_len + sizeof(*item));

	item = (void *)(&buf[data_len]);
	item->cp = buf;
	memcpy(item->cp, str, str_len + 1);
	list_head_init(&item->list);

	*__len = str_len;
	return item;
}

static struct strlist_item *pop_idle(struct list_head *head)
{
	struct strlist_item *item = NULL;

	if (!list_is_empty(head)) {
		item = list_first_entry(head, struct strlist_item, list);
		list_del(&item->list);
	}

	return item;
}

static struct strlist_item *alloc_item_sb(const char *str,
					  struct list_head *idle, size_t *__len)
{
	struct strlist_item *item = pop_idle(idle);

	if (item) {
		sb_trunc(item->sb, 0);
	} else {
		size_t sb_len = sizeof(struct strbuf);
		size_t data_len = align_up(sb_len, alignof(*item));
		char *buf = xmalloc(data_len + sizeof(*item));

		item = (void *)(&buf[data_len]);
		item->sb = (void *)buf;
		sb_init(item->sb, SB_ALLOC);
		list_head_init(&item->list);
	}

	*__len = sb_write_str(item->sb, str);
	return item;
}

static struct strlist_item *alloc_item_ref(const char *str,
					   struct list_head *idle)
{
	struct strlist_item *item = pop_idle(idle);

	if (!item)
		item = xmalloc(sizeof(*item));

	item->ref = str;
	list_head_init(&item->list);

	return item;
}

static size_t __sl_push(struct strlist *sl, const char *str, int forward)
{
	size_t len;
	struct strlist_item *item;

	switch (__sl_mode(sl->flags)) {
	case SL_USE_CP:
		item = alloc_item_cp(str, &len);
		break;
	case SL_USE_SB:
		item = alloc_item_sb(str, &sl->idle, &len);
		break;
	case SL_USE_REF:
		item = alloc_item_ref(str, &sl->idle);
	}

	if (forward)
		list_add(&item->list, &sl->head);
	else
		list_add_tail(&item->list, &sl->head);

	sl->items++;

	if (sl->flags & SL_RET_LEN) {
		if (sl->flags & SL_USE_REF)
			len = strlen(str);

		return len;
	}

	return -1;
}

size_t sl_push(struct strlist *sl, const char *str)
{
	return __sl_push(sl, str, 1);
}

size_t sl_push_back(struct strlist *sl, const char *str)
{
	return __sl_push(sl, str, 0);
}

char *sl_pop(struct strlist *sl)
{
	char *str = NULL;
	struct strlist_item *item = list_first_entry(&sl->head,
						     struct strlist_item, list);

	if (list_is_empty(&sl->head))
		return NULL;

	list_del(&item->list);

	switch (__sl_mode(sl->flags)) {
	case SL_USE_CP:
		str = item->cp;
		break;
	case SL_USE_SB:
		str = item->sb->buf;
		break;
	case SL_USE_REF:
		str = (char *)item->ref;
	}

	if (!(sl->flags & SL_USE_CP) && sl->flags & SL_POP_DUP)
		str = xstrdup(str);

	switch (__sl_mode(sl->flags)) {
	case SL_USE_SB:
	case SL_USE_REF:
		list_add(&item->list, &sl->idle);
	}

	sl->items--;
	return str;
}

static inline int is_brk(const char c)
{
	return isspace(c) || uc_iseoc(c);
}

static inline int is_brk_wc(wchar_t c)
{
	return iswspace(c) || uc_iseoc(c);
}

static void wrap_line(const char **end, const char **next, const char *__s,
		      const char *tail, size_t wrap)
{
	const char *s = __s;
	const char *txt_end = __s;
	const char *brk = NULL;
	const char *brk_end;
	size_t len = 0;

	while (s < tail) {
		size_t nbyte = uc_mbctype(*s);
		size_t width = 1;
		int ws = 0;
		wchar_t wc;

		switch (nbyte) {
		case _UC_9D:
		case _UC_9C:
		case _UC_9B:
			wc = uc_mbtowc(s);
			width += uc_iswide(wc);
			ws = iswspace(wc);

			if (is_brk_wc(wc))
				brk = s;

			break;
		case _UC_9A:
			ws = isspace(*s);

			if (is_brk(*s))
				brk = s;

			break;
		}

		if (brk == s)
			brk_end = ws ? txt_end : &s[nbyte];

		if (len + width > wrap) {
			if (!brk) {
				if (s == __s) {
					txt_end = &s[nbyte];
					s = txt_end;
				}

				break;
			}

			while (uc_ismbcb(*++brk));

			while (brk < tail && isspace(*brk))
				brk++;

			*end = brk_end;
			*next = brk;
			return;
		}

		if (!ws)
			txt_end = &s[nbyte];

		len += width;
		s = &s[nbyte];
	}

	*end = txt_end;
	*next = s;
}

void sl_read_line(struct strlist *sl, const char *str, size_t wrap)
{
	size_t len = strlen(str);
	const char *tail = &str[len];
	char *buf = xmalloc(len + 1);

	assert(!(sl->flags & SL_USE_REF));

	while (str < tail) {
		const char *end;
		const char *next;
		size_t n;

		wrap_line(&end, &next, str, tail, wrap);

		n = end - str;
		memcpy(buf, str, n);
		buf[n] = 0;

		sl_push_back(sl, buf);
		str = next;
	}

	free(buf);
}

char **sl_to_argv(struct strlist *sl)
{
	char **argv = xmalloc((sl->items + 1) * sizeof(*argv));
	char **ptr = argv;

	assert(!(sl->flags & SL_USE_SB));

	while (*ptr++ = sl_pop(sl));
	return argv;
}
