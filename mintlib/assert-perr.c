/*  assert-perr.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <_itoa.h>
#include <string.h>
#include <mintbind.h>
#include "lib.h"

#define assert_write(desc, buf, size) Fwrite (desc, size, buf)

/* This function, when passed an error number, a filename, and a line
   number, prints a message on the standard error stream of the form:
   	a.c:10: foobar: Unexpected error: Computer bought the farm
   It then aborts program execution via a call to `abort'.  */

void
__assert_perror_fail (int errnum,
		      const char *file, unsigned int line,
		      const char *function)
{
  char errbuf[1024];

  char _numbuf[11];
  char* numbuf;
  char* errormsg;
  
  _numbuf[10] = '\0';
  numbuf = _itoa_word (line, &_numbuf[10], 10, 0);
  errormsg = strerror_r (errnum, errbuf, sizeof errbuf);
  
#define COLONSPACE ": "
#define COLON ":"
#define ASSERTION "Unexpected error: "
#define PERIOD ".\n"

  /* Print the message.  */
  if (strcmp (program_invocation_short_name, "unknown application") != 0) {
    assert_write (STDERR_FILENO, program_invocation_short_name,
             strlen (program_invocation_short_name));
    assert_write (STDERR_FILENO, COLONSPACE, sizeof COLONSPACE - 1);
  }
  
  assert_write (STDERR_FILENO, file, strlen (file));
  assert_write (STDERR_FILENO, COLON, sizeof COLON - 1);
  assert_write (STDERR_FILENO, numbuf, strlen (numbuf));
  assert_write (STDERR_FILENO, COLONSPACE, sizeof COLONSPACE - 1);
  if (function != NULL) {
    assert_write (STDERR_FILENO, function, strlen (function));
    assert_write (STDERR_FILENO, COLONSPACE, sizeof COLONSPACE - 1);
  }
  assert_write (STDERR_FILENO, ASSERTION, sizeof ASSERTION - 1);
  assert_write (STDERR_FILENO, errormsg, strlen (errormsg));
  assert_write (STDERR_FILENO, PERIOD, sizeof PERIOD - 1);
  
  abort ();
}
