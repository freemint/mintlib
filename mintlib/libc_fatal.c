/*  libc_fatal.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mint/osbind.h>
#include "lib.h"

#ifdef __OPTIMIZE__
#pragma GCC optimize "-Os"
#endif

/* Abort with an error message.
   This function should write MESSAGE out in the most reliable way.
   It is called in situations like internal stdio lossage.  */

void
__libc_fatal (const char* message)
{
	size_t msglen = strlen (message);
	size_t i;
	static char const crlf[] = "\r\n";
	static char const colon[] = ": fatal libc error: ";
  
	Fwrite(STDERR_FILENO, strlen (program_invocation_name), program_invocation_name);
  	Fwrite(STDERR_FILENO, sizeof(colon) - 1, colon);
  
  	/* We better write a CRLF sequence here.  Of course this will make
     	   the function slower but we want the user to be able to read
     	   the message under all circumstances.  */
  	for (i = 0; i < msglen; i++) {
    		if (message[i] == '\n') 
      			Fwrite(STDERR_FILENO, sizeof(crlf) - 1, crlf);
    		else
      			Fwrite(STDERR_FILENO, 1, message + i);
  	}
  
  	abort ();
}
