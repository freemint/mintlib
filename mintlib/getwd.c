/*  getwd.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "lib.h"

char*
getwd (char *buf)
{
	char mybuf[PATH_MAX];
  
	if (buf == NULL) {
  		__set_errno (EINVAL);
  		return NULL;
  	}
  	
  	if (__getcwd (mybuf, PATH_MAX) == NULL) {
  	  __strerror_r (errno, buf, PATH_MAX);
  	  return NULL;
  	}
  	
  	return strcpy (buf, mybuf);  /* Ouch.  */
}

link_warning (getwd,
	      "the `getwd' function is a real killer and should not be used.")
