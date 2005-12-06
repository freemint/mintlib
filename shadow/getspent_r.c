/*  getspent_r.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <pwd.h>
#include <errno.h>
#include <paths.h>
#include <shadow.h>
#include <stdio.h>

static FILE* spfile = NULL;
static char* spfilename = _PATH_SHADOW;

extern int __fgetspent_r (FILE* stream, struct spwd* result_buf,
                          char* buffer, size_t buflen,
                          struct spwd** result);

int __getspent_r (struct spwd* result_buf, char* buffer,
                  size_t buflen, struct spwd** result)
{
  /* We handle that case gracefully.  Does the user deserve this?  */
  if (spfile == NULL)
    setspent ();
  return __fgetspent_r (spfile, result_buf, buffer, buflen, result);
}

void setspent (void)
{
  if (spfile == NULL)
    {
      /* FIXME: Should we lock the password file?  */
      spfile = fopen (spfilename, "rt");
      if (spfile == NULL)
        return;
    }

  rewind (spfile);
}

void endspent (void)
{
  if (spfile != NULL)
    {
      if (fclose (spfile) == 0)
        spfile = NULL;
    }
}

weak_alias (__getspent_r, getspent_r)
