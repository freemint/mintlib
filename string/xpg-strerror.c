/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
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

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>


/* Fill buf with a string describing the errno code in ERRNUM.  */
int __xpg_strerror_r(int errnum, char *buffer, size_t n)
{
	const char *error;

	if (!n)
		return ERANGE;
	error = strerror_r(errnum, buffer, n);
	if (error == NULL)
		return errno;
	if (strlen(error) >= n)
	{
		memcpy(buffer, error, n - 1);
		buffer[n - 1] = '\0';
		return ERANGE;
	}
	strcpy(buffer, error);
	return *error ? 0 : EINVAL;
}
