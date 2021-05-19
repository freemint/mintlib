/* Copyright (C) 1991, 1995, 1996 Free Software Foundation, Inc.
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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


/* Close all streams.  */
int
__fcloseall (void)
{
  /* Close all streams.  */
  register FILE *f, *next;
  for (f = __stdio_head; f != NULL; f = next)
  {
  	next = f->__next;
    if (__validfp(f))
      (void) fclose(f);
  }
  return 0;
}
weak_alias (__fcloseall, fcloseall)
