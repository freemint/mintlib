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
#include "lib.h"

/* Abort with an error message.
   This function should write MESSAGE out in the most reliable way.
   It is called in situations like internal stdio lossage.  */

void
__libc_fatal (register const char* message)
{
	size_t msglen = strlen (message);
	register size_t i;
	char* crlf = "\r\n";
	char* colon = ": fatal libc error: ";
  
	__write (STDERR_FILENO, program_invocation_name, 
      		 strlen (program_invocation_name));
  	__write (STDERR_FILENO, colon, sizeof colon - 1);
  
  	/* We better write a CRLF sequence here.  Of course this will make
     	   the function slower but we want the user to be able to read
     	   the message under all circumstances.  */
  	for (i = 0; i < msglen; i++) {
    		if (message[i] == '\n') 
      			__write (STDERR_FILENO, crlf, 2);
    		else
      			__write (STDERR_FILENO, (char*) message + i, 1);
  	}
  
  	abort ();
}
