/*  test-fdset.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Check the macros from sys/select.h.  */

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char sieve[FD_SETSIZE];
#define isprime(num) (sieve[num] == 0)

int 
main (int argc, char* argv[])
{
	fd_set mask;
	int i;
	int status = 0;
	int prime = 2;
	
	bzero (sieve, FD_SETSIZE);
	sieve[0] = 1;
	sieve[1] = 1;
	
       loop:
	while (1) {
		int j;
		
		for (j = prime * 2; j < FD_SETSIZE; j += prime)
			sieve[j] = 1;
		for (j = prime + 1; j < FD_SETSIZE; j++)
			if (isprime (j)) {
				prime = j;
				goto loop;
			}
		
		break;
	}
	
	FD_ZERO (&mask);
	
	/* We set all bits for primes.  */
	for (i = 0; i < FD_SETSIZE; i++)
		if (isprime (i)) FD_SET (i, &mask);
	
	for (i = 1; i < FD_SETSIZE; i++)
		if ((FD_ISSET (i, &mask) && !isprime (i))
		    || (!FD_ISSET (i, &mask) && isprime (i))) {
			printf ("FD_SET/FD_ISSET failed for %d\n", i);
			status = 1;
		}
	
	for (i = 0; i < FD_SETSIZE; i++)
		if (isprime (i)) FD_CLR (i, &mask);
	for (i = 0; i < FD_SETSIZE; i++)
		if (FD_ISSET (i, &mask)) {
			printf ("FD_CLR failed for %d\n", i);
			status = 1;
		}
		
	for (i = 0; i < FD_SETSIZE; i++)
		FD_SET (i, &mask);
	FD_ZERO (&mask);
	for (i = 0; i < FD_SETSIZE; i++)
		if (FD_ISSET (i, &mask)) {
			printf ("FD_ZERO failed for %d\n", i);
			status = 1;
		}

	if (status == 0)
		puts ("Test succeded.\n");
	else
		puts ("Test failed!\n");
				
	return status;
}
