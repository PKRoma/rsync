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

void show_file_stats()
{
	extern struct stats stats;

	rprintf(FINFO, "File statistics:\n"
		" %10s %12s\n"
		" %10ld %12.0f   files\n"
		" %10ld %12.0f     transferred\n"
		" %10ld %12.0f       new\n"
		"            %12.0f       literal data\n"
		"            %12.0f       matched data\n"
		" %10s %12s     up-to-date\n"
		" %10s %12s     removed\n"
		,
		"files", "bytes",
		(long) stats.num_files,
		(double)stats.total_size,
		(long) stats.num_transferred_files,
		(double)stats.total_transferred_size,
		(long) stats.num_new_files, (double) stats.new_files_size,
		(double)stats.literal_data,
		(double)stats.matched_data,
		"?", "?", "?", "?");

	rprintf(FINFO, "Network statistics\n");
	
	rprintf(FINFO,"Total bytes written: %.0f\n", 
		(double)stats.total_written);
	rprintf(FINFO,"Total bytes read: %.0f\n\n", 
		(double)stats.total_read);
}	
