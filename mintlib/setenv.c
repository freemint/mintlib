/* Copyright (C) 1992, 1995, 1996, 1997, 1998 Free Software Foundation, Inc.
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

/* Rehacked by Guido Flohr <gufl0000@stud.uni-sb.de> for MiNTLib.  */

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <errno.h>

#if _LIBC || HAVE_STDLIB_H
# include <stdlib.h>
#endif
#if _LIBC || HAVE_STRING_H
# include <string.h>
#endif
#if _LIBC || HAVE_UNISTD_H
# include <unistd.h>
#endif

#define __environ environ
extern char **environ;

/* In the MiNTLib we must keep the namespace clean.  */
#ifdef _LIBC
# define setenv __setenv
# define unsetenv __unsetenv
# define clearenv __clearenv
# define tfind __tfind
# define tsearch __tsearch
#endif

#undef USE_TSEARCH
#define KNOWN_VALUE(Str) NULL
#define STORE_VALUE(Str) do { } while (0)
#define LOCK
#define UNLOCK

/* If this variable is not a null pointer we allocated the current
   environment.  */
static char **last_environ;


int
setenv (const char* name, const char* value, int replace)
{
  register char **ep;
  register size_t size;
  const size_t namelen = strlen (name);
  const size_t vallen = strlen (value) + 1;

  LOCK;

  size = 0;
  if (__environ != NULL)
    {
      for (ep = __environ; *ep != NULL; ++ep)
	if (!strncmp (*ep, name, namelen) && (*ep)[namelen] == '=')
	  break;
	else
	  ++size;
    }

  if (__environ == NULL || *ep == NULL)
    {
      char **new_environ;
#ifdef USE_TSEARCH
      char *new_value;
#endif

      /* We allocated this space; we can extend it.  */
      new_environ = (char **) realloc (last_environ,
				       (size + 2) * sizeof (char *));
      if (new_environ == NULL)
	{
	  UNLOCK;
	  return -1;
	}

      /* See whether the value is already known.  */
#ifdef USE_TSEARCH
      new_value = alloca (namelen + 1 + vallen);
# ifdef _LIBC
      __mempcpy (__mempcpy (__mempcpy (new_value, name, namelen), "=", 1),
		 value, vallen);
# else
      memcpy (new_value, name, namelen);
      new_value[namelen] = '=';
      memcpy (&new_value[namelen + 1], value, vallen);
# endif

      new_environ[size] = KNOWN_VALUE (new_value);
      if (new_environ[size] == NULL)
#endif
	{
	  new_environ[size] = malloc (namelen + 1 + vallen);
	  if (new_environ[size] == NULL)
	    {
	      __set_errno (ENOMEM);
	      UNLOCK;
	      return -1;
	    }

#ifdef USE_TSEARCH
	  memcpy (new_environ[size], new_value, namelen + 1 + vallen);
#else
	  memcpy (new_environ[size], name, namelen);
	  new_environ[size][namelen] = '=';
	  memcpy (&new_environ[size][namelen + 1], value, vallen);
#endif
	}

      if (__environ != last_environ)
	memcpy ((char *) new_environ, (char *) __environ,
		size * sizeof (char *));

      new_environ[size + 1] = NULL;

      last_environ = __environ = new_environ;
    }
  else if (replace)
    {
#ifdef USE_TSEARCH
      char *new_value;
#endif
      char *np;

      /* The existing string is too short; malloc a new one.  */
#ifdef USE_TSEARCH
      new_value = alloca (namelen + 1 + vallen);
# ifdef _LIBC
      __mempcpy (__mempcpy (__mempcpy (new_value, name, namelen), "=", 1),
		 value, vallen);
# else
      memcpy (new_value, name, namelen);
      new_value[namelen] = '=';
      memcpy (&new_value[namelen + 1], value, vallen);
# endif

      np = KNOWN_VALUE (new_value);
      if (np == NULL)
#endif
	{
	  np = malloc (namelen + 1 + vallen);
	  if (np == NULL)
	    {
	      UNLOCK;
	      return -1;
	    }

#ifdef USE_TSEARCH
	  memcpy (np, new_value, namelen + 1 + vallen);
#else
	  memcpy (np, name, namelen);
	  np[namelen] = '=';
	  memcpy (&np[namelen + 1], value, vallen);
#endif
	}

      /* Keep the old value around.  */
      STORE_VALUE (*ep);
      *ep = np;
    }

  UNLOCK;

  return 0;
}

void
unsetenv (name)
     const char *name;
{
  const size_t len = strlen (name);
  char **ep;

  LOCK;

  for (ep = __environ; *ep != NULL; ++ep)
    if (!strncmp (*ep, name, len) && (*ep)[len] == '=')
      {
	/* Found it.  Remove this pointer by moving later ones back.  */
	char **dp = ep;

	/* Store the value so that we can reuse it later.  */
	STORE_VALUE (*ep);

	do
	  dp[0] = dp[1];
	while (*dp++);
	/* Continue the loop in case NAME appears again.  */
      }

  UNLOCK;
}

/* The `clearenv' was planned to be added to POSIX.1 but probably
   never made it.  Nevertheless the POSIX.9 standard (POSIX bindings
   for Fortran 77) requires this function.  */
int
clearenv ()
{
  LOCK;

  if (__environ == last_environ && __environ != NULL)
    {
      /* We allocated this environment so we can free it.  Store all the
         strings.  */
      char **ep = __environ;
      while (*ep != NULL)
	STORE_VALUE (*ep++);

      free (__environ);
      last_environ = NULL;
    }

  /* Clear the environment pointer removes the whole environment.  */
  __environ = NULL;

  UNLOCK;

  return 0;
}
#ifdef _LIBC
# ifdef HAVE_WEAK_SYMBOLS
#  undef setenv
#  undef unsetenv
#  undef clearenv
weak_alias (__setenv, setenv)
weak_alias (__unsetenv, unsetenv)
weak_alias (__clearenv, clearenv)
# endif
#endif
