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

#include <stdio.h>
#include "lib.h"


/* Open a new stream on the given magic cookie descriptor.  */
FILE *
fopencookie (void *cookie, const char *mode, __io_functions functions)
{
  __io_mode m;
  FILE *f;

  if (!__getmode (mode, &m))
    return NULL;

  f = __newstream ();
  if (f == NULL)
    return NULL;

  f->__cookie = cookie;
  f->__mode = m;
  f->__io_funcs = functions;
  f->__room_funcs = __default_room_functions;
  f->__seen = 1;

  return f;
}
