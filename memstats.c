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

/** Size in bytes of main flist **/
size_t mems_main_flist;

/** Total allocated to file_structs **/
size_t mems_file_structs;


/** Total allocation and overhead in string_areas */
size_t mems_string_areas;
size_t mems_exclude_struct;
size_t mems_map_struct;
size_t mems_tags;
size_t mems_delete_list;
size_t mems_hlink_list;

/**
 * If our C library can get malloc statistics, then show them to FINFO
 **/
void show_mem_stats(void)
{
	rprintf(FINFO, "memory usage:\n"
		"  %10ld  file_list\n"
		"  %10ld  hlink_list\n"
		"  %10ld  file_structs (and associated data)\n"
		"  %10ld  string_areas\n"
		"  %10ld  exclude_structs\n"
		"  %10ld  map_structs\n"
		"  %10ld  tags\n"
		"  %10ld  delete_list\n"
		,
		(long) mems_main_flist,
		(long) mems_hlink_list,
		(long) mems_file_structs,
		(long) mems_string_areas,
		(long) mems_exclude_struct,
		(long) mems_map_struct,
		(long) mems_tags,
		(long) mems_delete_list);
}


void * malloc_counted(size_t howmuch, size_t *pot)
{
	*pot += howmuch;
	return malloc(howmuch);
}
