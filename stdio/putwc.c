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
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Modified for MiNTLib by Guido Flohr <guido@freemint.de>.  */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <errno.h>

__typeof__(putwc) __putwc;

wint_t __putwc (wchar_t wc, FILE *stream)
{
	char s[MB_CUR_MAX];
	int i, len;
	
	if ((len = (int)wcrtomb(s, wc, NULL)) < 0)
		return WEOF;
	for (i = 0; i < len; i++)
		if (__putc(s[i], stream) == EOF)
			return WEOF;
	return wc;
}

/* Write the character C to STREAM.  */
wint_t
putwc (wchar_t c, FILE *stream)
{
  if (!__validfp (stream) || !stream->__mode.__write)
    {
      if (__validfp (stream))
      	stream->__error = 1;

      __set_errno (EINVAL);
      return WEOF;
    }

  return __putwc (c, stream);
}
