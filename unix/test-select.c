/*  test-select.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Minimal check for select (and thus for poll).  */

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <test-skeleton.c>

#define MAX_HANDLE(a, b) (a > b ? a : b)

int 
do_test (int argc, char* argv[])
{
	fd_set rfds, wfds, xfds;
	struct timeval timeout = { 1, 0 };
	int retval;
	int status = 0;
	int i;
	FILE* f1 = tmpfile ();
	FILE* f2 = tmpfile ();
	int fd1, fd2;
	
	if (f1 == NULL || f2 == NULL) {
		printf ("can't create temporary files\n");
		return 1;
	}
	
	fd1 = fileno (f1);
	fd2 = fileno (f2);
	
	FD_ZERO (&rfds);
	FD_ZERO (&wfds);
	FD_ZERO (&xfds);
	FD_SET (fd1, &wfds);
	FD_SET (fd2, &rfds);
	
	retval = select (1 + MAX_HANDLE (fd1, fd2), 
			 &rfds, &wfds, &xfds, &timeout);
	
	if (retval < 0) {
		perror ("select");
		return 1;
	} else if (retval == 0) {
		fputs ("error: select timeout\n", stderr);
		return 1;
	} else if (retval != 2) {
		fprintf (stderr, "error: select returned %d (funny)\n", retval);
		status = 1;
	}

	if (!FD_ISSET (fd1, &wfds)) {
		status = 1;
		fputs ("error: empty file not ready for writing.\n", stderr);
	}
	FD_CLR (fd1, &wfds);
	
	if (!FD_ISSET (fd2, &rfds)) {
		status = 1;
		fputs ("error: empty file ready not for reading.\n", stderr);
	}
	FD_CLR (fd2, &rfds);
	
	for (i = 0; i < FD_SETSIZE; i++) {
		if (FD_ISSET (i, &rfds)) {
			fprintf (stderr, "\
error: descriptor %d ready for reading\n", i);
			status = 1;
		}
		if (FD_ISSET (i, &wfds)) {
			fprintf (stderr, "\
error: descriptor %d ready for writing\n", i);
			status = 1;
		}
		if (FD_ISSET (i, &xfds)) {
			fprintf (stderr, "\
error: exceptional condition on descriptor %d\n", i);
			status = 1;
		}
	}
	
	if (status == 0)
		puts ("Test succeded.\n");
	else
		puts ("Test failed!\n");
				
	return status;
}
