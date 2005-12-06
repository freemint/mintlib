/* Copyright (C) 1992, 1996 Free Software Foundation, Inc.
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

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#ifdef __MINT__
extern char* __initstate (unsigned int __seed, char *__arg_state, int __n);
extern long __random (void);
#endif

char *
strfry (char *string)
{
  static int init = 0;
#ifndef __MINT__
  static struct random_data rdata;
#endif
  size_t len, i;

  if (!init)
    {
      static int state[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
#ifndef __MINT__
      rdata.state = NULL;
      __initstate_r (time ((time_t *) NULL), state, 8, &rdata);
#else
      __initstate (time ((time_t *) NULL), (char*) state, (int) sizeof state);
#endif
      init = 1;
    }

  len = strlen (string);
  for (i = 0; i < len; ++i)
    {
      int32_t j;
      char c;

#ifndef __MINT__
      __random_r (&rdata, &j);
#else
      j = __random ();
#endif
      j %= len;

      c = string[i];
      string[i] = string[j];
      string[j] = c;
    }

  return string;
}
