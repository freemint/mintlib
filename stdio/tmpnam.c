/*  tmpnam.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

/* In diraccess.c.  */
extern const char* __get_tmpdir (const char*, int try_tmpdir);

static char tmpnam_buffer[L_tmpnam];

char* tmpnam (user_buf)
	char* user_buf;
{
  	char* tmpdir = (char*) __get_tmpdir (NULL, 0);
  	char def_buf[L_tmpnam];		/* To be thread-safe when user_buf
  					   != NULL.  */
  	char* buf = user_buf == NULL ? def_buf : user_buf;
  	size_t len = strlen (tmpdir);
  
  	if (tmpdir == NULL)
  		return NULL;
  	
  	memcpy (buf, tmpdir, len);
  	if (buf[len - 1] != '/' && buf[len - 1] != '\\') {
      		if (__mint)
        		buf[len] = '/';
      		else
        		buf[len] = '\\';
      		len++;
    	}
  	memcpy (buf + len, "XXXXXX\000", 7);
  
  	if (mktemp (buf) == NULL)
    		return NULL;
  
  	if (user_buf == NULL)
    		return (char*) memcpy (tmpnam_buffer, buf, L_tmpnam);
  	
  	return buf;
}
