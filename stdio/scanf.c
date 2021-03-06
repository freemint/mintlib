/* Copyright (C) 1991, 1995, 1996, 1997 Free Software Foundation, Inc.
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

#include <stdarg.h>
#include <stdio.h>


/* Read formatted input from stdin according to the format string FORMAT.  */
/* VARARGS1 */
int
scanf (const char *format, ...)
{
  va_list arg;
  int done;

  va_start (arg, format);
#ifdef USE_IN_LIBIO
  done = _IO_vfscanf (stdin, format, arg, NULL);
#else
  done = vfscanf (stdin, format, arg);
#endif
  va_end (arg);

  return done;
}
