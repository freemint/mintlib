/* Copyright (C) 1991, 1994, 1995, 1996, 1997 Free Software Foundation, Inc.
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
#include "lib.h"



/* Replace STREAM, opening it on FILENAME.  */
FILE *
freopen (const char *filename, const char *mode, FILE *stream)
{
  __io_mode m;
  void *cookie;

  if (!__getmode (mode, &m))
    {
      (void) fclose (stream);
      __set_errno (EINVAL);
      return NULL;
    }

  if (stream->__mode.__write)
    /* Flush the stream.  */
    (void) fflush (stream);

  /* Open the file, attempting to preserve the old cookie value.  */
  cookie = stream->__cookie;
  if (__stdio_reopen (filename, m, &cookie,
		      stream->__seen ?
		      stream->__io_funcs.__close :
		      __stdio_close))
    {
      int save = errno;
      (void) fclose (stream);
      __set_errno (save);
      return NULL;
    }

  /* Close the stream, first disabling its cookie close function because
     __stdio_reopen has already dealt with closing the old cookie.  */
  stream->__seen = 1;		/* It might have no functions yet.  */
  stream->__io_funcs.__close = NULL;
  (void) fclose (stream);

  stream->__magic = _IOMAGIC;
  stream->__cookie = cookie;
  stream->__mode = m;

  return stream;
}
