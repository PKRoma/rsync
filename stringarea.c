/* 
   Copyright (C) Andrew Tridgell 1996
   Copyright (C) Paul Mackerras 1996
   Copyright (C) 2001, 2002 by Martin Pool <mbp@samba.org>
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "rsync.h"

struct string_area {
	char *base;
	char *end;
	char *current;
	struct string_area *next;
};

struct string_area *string_area_new(int size)
{
	struct string_area *a;
	extern size_t mems_string_areas;

	if (size <= 0)
		size = ARENA_SIZE;
	a = malloc(sizeof(*a));
	if (!a)
		out_of_memory("string_area_new");
	a->current = a->base = malloc(size);
	if (!a->current)
		out_of_memory("string_area_new buffer");
	a->end = a->base + size;
	a->next = NULL;

	mems_string_areas += sizeof(*a) + size;

	return a;
}

void string_area_free(struct string_area *a)
{
	struct string_area *next;

	for (; a; a = next) {
		next = a->next;
		free(a->base);
	}
}

char *string_area_malloc(struct string_area **ap, int size)
{
	char *p;
	struct string_area *a;

	/* does the request fit into the current space? */
	a = *ap;
	if (a->current + size >= a->end) {
		/* no; get space, move new string_area to front of the list */
		a = string_area_new(size > ARENA_SIZE ? size : ARENA_SIZE);
		a->next = *ap;
		*ap = a;
	}

	/* have space; do the "allocation." */
	p = a->current;
	a->current += size;
	return p;
}

char *string_area_strdup(struct string_area **ap, const char *src)
{
	char *dest = string_area_malloc(ap, strlen(src) + 1);
	return strcpy(dest, src);
}

