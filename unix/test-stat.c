/*  test-stat.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Check if struct stat matches the kernel definition.  */

#include <stdio.h>
#include <sys/stat.h>

int 
main (int argc, char* argv[])
{
	if (sizeof (struct stat) != 128) {
		fprintf (stderr, "Ooooooops, struct stat has wrong size (%ld)\n",
			 sizeof (struct stat));
		return 1;
	}
	return 0;
}
