/* Copyright (C) 1994, 1996, 1997, 2001 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <time.h>
#include <sys/timeb.h>
#include <sys/time.h>
#include "lib.h"

int __ftime64(struct timeb64 *timebuf)
{
	struct timeval64 now;

	if (__gettimeofday64(&now, NULL) != 0)
		return -1;
	timebuf->time = now.tv_sec;
	timebuf->millitm = now.tv_usec / 1000;

	timebuf->timezone = 0;
	timebuf->dstflag = 0;

	return 0;
}

link_warning (__ftime64,
	      "`ftime' is deprecated, use `gettimeofday' instead")
