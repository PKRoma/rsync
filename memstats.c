/*
 * Copyright (C) 2002 by Martin Pool
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "rsync.h"

/**
 * @file memstats.c
 *
 * Show moderately high-level information about how much memory was
 * used for different things.  The counting relies on various parts of
 * the program updating counters as they use memory, so at first it
 * will not be super accurate.
 **/

/* TODO: Perhaps show these numbers with commas to make them a bit
 * more readable. */

/**
 * If our C library can get malloc statistics, then show them to FINFO
 **/
void show_mem_stats(void)
{
	extern struct stats stats;
	
	rprintf(FINFO, "Memory usage:\n"
		"  %10ld    bytes file_list\n"
		"    %10ld  bytes flist_size\n"  
		"  %10ld    bytes hlink_list\n"
		"  %10ld    bytes file_structs (and associated data)\n"
		"  %10ld    bytes string_areas\n"
		"  %10ld    bytes exclude_structs\n"
		"  %10ld    bytes map_structs\n"
		"  %10ld    bytes tags\n"
		"  %10ld    bytes delete_list\n"
		,
		(long) stats.main_flist,
		(long) stats.flist_size,
		(long) stats.hlink_list,
		(long) stats.file_structs,
		(long) stats.string_areas,
		(long) stats.exclude_struct,
		(long) stats.map_struct,
		(long) stats.tags,
		(long) stats.delete_list);
}


void * malloc_counted(size_t howmuch, size_t *pot)
{
	*pot += howmuch;
	return malloc(howmuch);
}


/**
 * If our C library can get malloc statistics, then show them to FINFO
 **/
void show_malloc_stats(void)
{
#ifdef HAVE_MALLINFO
	struct mallinfo mi;

	mi = mallinfo();

	rprintf(FINFO, "VM statistics:\n"
		"  %10s\n",
		"bytes");

	rprintf(FINFO, "  %10ld      from sbrk()\n", (long) mi.arena);
	rprintf(FINFO, "  %10ld      from mmap()\n", (long) mi.hblkhd);
	rprintf(FINFO, "  %10ld      in use\n", (long) mi.uordblks);
	rprintf(FINFO, "  %10ld      free in heap\n", (long) mi.fordblks);
#endif				/* HAVE_MALLINFO */
}
