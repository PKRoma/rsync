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

extern time_t starttime;

void show_file_stats(void)
{
	extern struct stats stats;

	rprintf(FINFO, "File statistics:\n"
		"  %10s %12s\n"
		"  %10ld %12.0f                         files\n"
		"  %10ld %12.0f                           transferred\n"
		"  %10ld %12.0f                             new\n"
		"             %12.0f                         literal data\n"
		"             %12.0f                         matched data\n"
		" %10s %12s                               up-to-date\n"
		" %10s %12s                               removed\n"
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
}


void show_net_stats(void)
{
	time_t t = time(NULL);

	/* stats.total_written is are accumulated in writefd, which is
	 * called after compression of data.  It might be interesting
	 * to also hook in above that level to keep track of the
	 * amount of data before compression. */
	
	rprintf(FINFO, "Network statistics\n"
		"  %10s %10s %10s\n"
		"  %10.0f %10.0f %10.2f                total bytes\n"
		,
		"read", "write", "bytes/s",
		(double) stats.total_read,
		(double) stats.total_written,
		(stats.total_written+stats.total_read)/(0.5 + (t-starttime)));
}


void show_time_stats(void)
{
	rprintf(FINFO, "Timing statistics\n"
		"  %10s\n"
		"  %10ld                                      elapsed\n"
		,
		"seconds",
		(long) time(NULL)-starttime);
}
