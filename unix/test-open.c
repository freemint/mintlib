/*  test-open.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Check if open works correctly.  */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int 
main (int argc, char* argv[])
{
	char* dir = tmpnam (NULL);
	int failure = 0;
	int fd;
	
	if (dir == NULL) {
		perror ("tmpnam");
		return -1;
	}

	if (mkdir (dir, 0755) != 0) {
		perror ("mkdir");
		return -1;
	}
	
	/* Change into that directory.  */
	if (chdir (dir) != 0) {
		perror ("chdir");
		remove (dir);
		return -1;
	}
		
	/* Try to open that directory for writing.  */
	if (open (dir, O_WRONLY) >= 0) {
		fprintf (stderr, "can open directory `%s' for writing!!!\n", 
			 dir);
		failure = 1;
	}
	
	/* Check if errno is EISDIR.  */
	if (errno != EISDIR) {
		fprintf (stderr, "open (directory): expected `%s', got `%s'\n",
			 strerror (EISDIR), strerror (errno));
		failure = 1;
	}
	
	/* Open a non-existing file for reading.  */
	if (open ("nonexist", O_RDONLY) >= 0) {
		fprintf (stderr, "can open non-existing file for reading!!!\n");
		failure = 1;
	}
	
	/* Check if errno is ENOENT.  */
	if (errno != ENOENT) {
		fprintf (stderr, "open (nonexist): expected `%s', got `%s'\n",
			 strerror (ENOENT), strerror (errno));
		failure = 1;
	}
	
	/* Open a non-existing file for reading.  */
	if (open ("nodir/nonexist", O_RDONLY) >= 0) {
		fprintf (stderr, "can open non-existing file for reading!!!\n");
		failure = 1;
	}
	
	/* Check if errno is ENOENT.  */
	if (errno != ENOENT) {
		fprintf (stderr, "open (nodir/nonexist): expected `%s', got `%s'\n",
			 strerror (ENOENT), strerror (errno));
		failure = 1;
	}
	
	/* Open a file for writing.  */
	fd = open ("exist", O_WRONLY | O_CREAT);
	if (fd < 0) {
		perror ("open for writing");
		failure = 1;
		goto lose;
	}

	if (close (fd) != 0) {
		perror ("close");
		failure = 1;
		goto lose;
	}
	
       lose:
	(void) remove ("exist");
	(void) chdir ("/");
	(void) remove (dir);
		
	return failure;
}
