/* Copyright (C) 1991, 1992, 1997 Free Software Foundation, Inc.
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

/* Modified (linker warning) for MiNTLib by Guido Flohr <guido@freemint.de>.  */

#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>


/* Write formatted output to S according to the format string
   FORMAT, using the argument list in ARG.  */
int
vswprintf (wchar_t *s, size_t maxlen, const wchar_t *format, va_list arg)
{
  int done;
  FILE f;

  memset ((void *) &f, 0, sizeof (f));
  f.__magic = _IOMAGIC;
  f.__mode.__write = 1;
  f.__bufp = f.__buffer = (char *) s;
  f.__put_limit = (char *) (s + maxlen);
  f.__bufsize = (size_t) (f.__put_limit - f.__bufp);
  f.__get_limit = f.__buffer;
  f.__room_funcs.__output = NULL;
  f.__seen = 1;

  done = vfwprintf (&f, format, arg);
  *f.__bufp = '\0';

  return done;
}
