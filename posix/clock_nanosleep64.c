/* High-resolution sleep with the specified clock.
   Copyright (C) 2000-2012 Free Software Foundation, Inc.
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
   <http://www.gnu.org/licenses/>.  */

#include <assert.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include "lib.h"

int __clock_nanosleep_time64 (clockid_t clock_id, int flags, const struct timespec64 *req, struct timespec64 *rem)
{
	__int32_t high;
	struct timespec req32;
	struct timespec rem32;
	int ret;

	high = req->tv_sec >> 32;
	if (high != 0)
	{
		__set_errno(EINVAL);
		return -1;
	}
	req32.tv_sec = req->tv_sec;
	req32.tv_nsec = req->tv_nsec;
	ret = clock_nanosleep(clock_id, flags, &req32, &rem32);
	if (ret < 0 && errno == EINTR && rem)
	{
		rem->tv_sec = req32.tv_sec;
		rem->tv_nsec = req32.tv_nsec;
	}
	return ret;
}
