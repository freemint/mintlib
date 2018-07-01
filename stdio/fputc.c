/* Copyright (C) 1991, 1996, 1997, 1998, 1999 Free Software Foundation, Inc.
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
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Modified for MiNTLib by Guido Flohr <guido@freemint.de>.  */

#include <errno.h>
#include <stdio.h>

#if __GNUC_PREREQ(7, 0)
# pragma GCC diagnostic ignored "-Wnonnull-compare"
#endif

/* Write the character C to STREAM.  */
int
fputc (c, stream)
     int c;
     FILE *stream;
{
  if (!__validfp (stream) || !stream->__mode.__write)
    {
      if __validfp (stream)
      	stream->__error = 1;
      	
      __set_errno (EINVAL);
      return EOF;
    }

  return __putc (c, stream);
}

#ifndef fputc
weak_alias (fputc, fputc_unlocked)
#endif
