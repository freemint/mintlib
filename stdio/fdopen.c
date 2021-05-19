/* Copyright (C) 1991, 1992, 1993, 1996 Free Software Foundation, Inc.
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
#include <fcntl.h>
#include <unistd.h>
#include "lib.h"

__typeof__(fcntl) __fcntl;

/* Open a new stream on a given system file descriptor.  */
FILE *
__fdopen (int fd, const char *mode)
{
  register FILE *stream;
  __io_mode m;
  int dflags;

  if (!__getmode (mode, &m))
    return NULL;

  /* Verify the FD is valid and allows the access MODE specifies.  */

  dflags = __fcntl (fd, F_GETFL);
  if (dflags == -1)
    /* FD was invalid; fcntl has already set errno.  */
    return NULL;

  /* Check the access mode.  */
  switch (dflags & O_ACCMODE)
    {
    case O_RDONLY:
      if (!m.__read)
	{
	  __set_errno (EBADF);
	  return NULL;
	}
      break;
    case O_WRONLY:
      if (!m.__write)
	{
	  __set_errno (EBADF);
	  return NULL;
	}
      break;
    }

  stream = __newstream ();
  if (stream == NULL)
    return NULL;

  stream->__cookie = (void *) ((long) fd);
  stream->__mode = m;

  return stream;
}

weak_alias (__fdopen, fdopen)
