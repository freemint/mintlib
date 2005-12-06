/*  getpwent_r.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <pwd.h>
#include <errno.h>
#include <stdio.h>

#ifndef HAVE_WEAK_SYMBOLS
# define __getpwent_r(result_buf, buffer, buflen, result) \
  getpwent_r(result_buf, buffer, buflen, result)
# define __fgetpwent_r(stream, result_buf, buffer, buflen, result) \
  fgetpwent_r(stream, result_buf, buffer, buflen, result)
#endif

static FILE* pwfile = NULL;
static char* pwfilename = "/etc/passwd";

extern int __fgetpwent_r (FILE* stream, struct passwd* result_buf,
                          char* buffer, size_t buflen,
                          struct passwd** result);

int __getpwent_r (struct passwd* result_buf, char* buffer,
                  size_t buflen, struct passwd** result)
{
  /* We handle that case gracefully.  Does the user deserve this?  */
  if (pwfile == NULL)
    setpwent ();
  return __fgetpwent_r (pwfile, result_buf, buffer, buflen, result);
}

void setpwent (void)
{
  if (pwfile == NULL)
    {
      /* FIXME: Should we lock the password file?  */
      pwfile = fopen (pwfilename, "rt");
      if (pwfile == NULL)
        return;
    }

  rewind (pwfile);
}

void endpwent (void)
{
  if (pwfile != NULL)
    {
      if (fclose (pwfile) == 0)
        pwfile = NULL;
    }
}

weak_alias (__getpwent_r, getpwent_r)
