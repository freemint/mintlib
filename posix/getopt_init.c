/* Perform additional initialization for getopt functions in GNU libc.
   Copyright (C) 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

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

/* Attention: this file is *not* necessary when the GNU getopt functions
   are used outside the GNU libc.  Some additional functionality of the
   getopt functions in GNU libc require this additional work.  */

/* Adapted to MiNTLib by Guido Flohr.  */

#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

extern char** environ;

/* Variable to synchronize work.  */
char *__getopt_nonoption_flags;

static pid_t __libc_pid;

/* Convert VALUE into ASCII in base BASE (2..36).
   Write backwards starting the character just before BUFLIM.
   Return the address of the first (left-to-right) character in the number.
   Use upper case letters iff UPPER_CASE is nonzero.  */

static char _itoa_upper_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
static char _itoa_lower_digits[] = "0123456789abcdefghijklmnopqrstuv";
#ifdef __TURBOC__
static char *
#else
static inline char *
#endif
_itoa_word (unsigned long value, char *buflim,
	    unsigned int base, int upper_case)
{
  const char *digits = upper_case ? _itoa_upper_digits : _itoa_lower_digits;
  char *bp = buflim;

  switch (base)
    {
#define SPECIAL(Base)							      \
    case Base:								      \
      do								      \
	*--bp = digits[value % Base];					      \
      while ((value /= Base) != 0);					      \
      break

      SPECIAL (10);
      SPECIAL (16);
      SPECIAL (8);
    default:
      do
	*--bp = digits[value % base];
      while ((value /= base) != 0);
    }
  return bp;
}


/* Remove the environment variable "_<PID>_GNU_nonoption_argv_flags_" if
   it is still available.  If the getopt functions are also used in the
   application it does not exist anymore since it was saved for the use
   in getopt.  */
void
__getopt_clean_environment (void)
{
  /* Bash 2.0 puts a special variable in the environment for each
     command it runs, specifying which ARGV elements are the results
     of file name wildcard expansion and therefore should not be
     considered as options.  */
  static const char envvar_tail[] = "_GNU_nonoption_argv_flags_";
  char var[100];
  char *cp, **ep;
  size_t len;
  
  /* Generate name of the environment variable.  We must know the PID
     and we must not use `sprintf'.  */
  if (__libc_pid == 0)
    __libc_pid = getpid ();

  /* Construct "_<PID>_GNU_nonoption_argv_flags_" string.  */
  cp = memcpy (&var[sizeof (var) - sizeof (envvar_tail)], envvar_tail,
	       sizeof (envvar_tail));
  cp = _itoa_word (__libc_pid, cp, 10, 0);
  *--cp = '_';
  len = (var + sizeof (var) - 1) - cp;

  for (ep = environ; *ep != NULL; ++ep)
    if (!strncmp (*ep, cp, len) && (*ep)[len] == '=')
      {
	/* Found it.  Store this pointer and move later ones back.  */
	char **dp = ep;
	__getopt_nonoption_flags = &(*ep)[len + 1];
	do
	  dp[0] = dp[1];
	while (*dp++);
	/* Continue the loop in case the name appears again.  */
      }
}
