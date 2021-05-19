/* Copyright (C) 1991, 1992, 1997, 1998 Free Software Foundation, Inc.
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

/* Modified for MiNTLib by Guido Flohr <guido@freemint.de>.  */

#include <errno.h>
#include <stdio.h>
#include <string.h>

#ifdef fputs_unlocked
# undef fputs_unlocked
#endif

/* Write the string S to STREAM.  */
int
fputs (const char *s, FILE *stream)
{
  const size_t len = strlen (s);
  if (len == 1)
    return putc (*s, stream) == EOF ? EOF : 0;
  if (fwrite ((void *) s, 1, len, stream) != len)
    return EOF;
  return 0;
}
weak_alias (fputs, fputs_unlocked)
