/* Copyright (C) 1996, 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.

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

/* Adapted to MiNTLib by Guido Flohr <guido@freemint.de>,
   18 Sep 1999.  */

#include <stdlib.h>   
#include <utmp.h>


/* Local buffer to store the result.  */
static struct utmp buffer;

__typeof__(getutline_r) __getutline_r;
__typeof__(getutline) __getutline;

struct utmp *
__getutline (const struct utmp *line)
{
  struct utmp *result;

  if (__getutline_r (line, &buffer, &result) < 0)
    return NULL;

  return result;
}
weak_alias (__getutline, getutline)
