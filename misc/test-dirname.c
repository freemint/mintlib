/* Test program for dirname function a la XPG.
   Copyright (C) 1996 Free Software Foundation, Inc.
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

#define _GNU_SOURCE	1
#include <libgen.h>
#include <stdio.h>
#include <string.h>


extern int test __P ((const char *input, const char *result));

int
test (input, result)
     const char *input;
     const char *result;
{
  int retval;
  char *cp;
  cp = strdupa (input);
  cp = dirname (cp);
  retval = strcmp (cp, result);
  if (retval)
    printf ("dirname(\"%s\") should be \"%s\", but is \"%s\"\n",
	    input, result, cp);
  return retval;
}

int main __P ((int argc, char *argv[]));
int
main (argc, argv)
     int argc;
     char *argv[];
{
  int result = 0;

  /* These are the examples given in XPG4.2.  */
  result |= test ("/usr/lib", "/usr");
  result |= test ("/usr", "/");
  result |= test ("usr", ".");
  result |= test ("/", "/");
  result |= test (".", ".");
  result |= test ("..", ".");

  return result != 0;
}
