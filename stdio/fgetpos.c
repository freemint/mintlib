/* Copyright (C) 1991, 1996, 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <stdio.h>

#undef	fgetpos


/* Put the current position of STREAM in *POS.  */
int
fgetpos (FILE *stream, fpos_t *pos)
{
  if (!__validfp (stream) || pos == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }

  *pos = ftell (stream);
  if (*pos < 0L)
    return -1;
  return 0;
}
