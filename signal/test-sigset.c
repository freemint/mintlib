/* Test signal routines.  */

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

int
main (int argc, char* argv[])
{
	sigset_t mask;
	int status = 0;

	__sigfillset (&mask);
	if ((unsigned long) mask != 0xffffffffUL)
		printf ("__sigfillset FAIL\n"), status = 1;
	else
		printf ("__sigfillset ok\n");

	__sigemptyset (&mask);
	if ((unsigned long) mask != 0UL)
		printf ("__sigemptyset FAIL\n"), status = 1;
	else
		printf ("__sigemptyset ok\n");
	
	sigfillset (&mask);
	if ((unsigned long) mask != 0xffffffffUL)
		printf ("sigfillset FAIL\n"), status = 1;
	else
		printf ("sigfillset ok\n");
	
	sigemptyset (&mask);
	if ((unsigned long) mask != 0UL)
		printf ("sigemptyset FAIL\n"), status = 1;
	else
		printf ("sigemptyset ok\n");
	
	mask = 0xff00ff00;
	__sigaddset (&mask, 1);
	if ((unsigned long) mask != 0xff00ff01UL)
		printf ("__sigaddset FAIL\n"), status = 1;
	else
		printf ("__sigaddset ok\n");
	
	__sigdelset (&mask, 1);
	if ((unsigned long) mask != 0xff00ff00UL)
		printf ("__sigdelset FAIL\n"), status = 1;
	else
		printf ("__sigdelset ok\n");
	
	sigaddset (&mask, 1);
	if ((unsigned long) mask != 0xff00ff01UL)
		printf ("sigaddset FAIL\n"), status = 1;
	else
		printf ("sigaddset ok\n");
	
	sigdelset (&mask, 1);
	if ((unsigned long) mask != 0xff00ff00UL)
		printf ("sigdelset FAIL\n"), status = 1;
	else
		printf ("sigdelset ok\n");
	
	{
		sigset_t left  = (sigset_t) 0xff00ff00UL;
		sigset_t right = (sigset_t) 0x0ff00ff0UL;
		
		__sigandset (&mask, &left, &right);
		if ((unsigned long) mask != 0x0f000f00UL)
			printf ("__sigandset FAIL\n"), status = 1;
		else
			printf ("__sigandset ok\n");
		
		sigandset (&mask, &left, &right);
		if ((unsigned long) mask != 0x0f000f00UL)
			printf ("sigandset FAIL\n"), status = 1;
		else
			printf ("sigandset ok\n");
		
		__sigorset (&mask, &left, &right);
		if ((unsigned long) mask != 0xfff0fff0UL)
			printf ("__sigorset FAIL\n"), status = 1;
		else
			printf ("__sigorset ok\n");
		
		sigorset (&mask, &left, &right);
		if ((unsigned long) mask != 0xfff0fff0UL)
			printf ("sigorset FAIL\n"), status = 1;
		else
			printf ("sigorset ok\n");
		
	}
	
	{
		int i;
		
		sigemptyset (&mask);
		for (i = 1; i < NSIG; i++)
			sigaddset (&mask, i);
		for (i = 1; i < NSIG; i++)
			sigdelset (&mask, i);
		if ((unsigned long) mask != 0UL)
			printf ("sigaddset/sigdelset FAIL\n"), status = 1;
		else
			printf ("sigaddset/sigdelset ok\n");
		
	}
	
	{
		int i;
		
		sigemptyset (&mask);
		for (i = 1; i < NSIG; i += 2) 
			sigaddset (&mask, i);
		for (i = 1; i < NSIG; i += 2)
			if (!sigismember (&mask, i))
				printf ("sigismember for %i failed\n", i), status = 1;
		for (i = 2; i < NSIG; i += 2)
			if (sigismember (&mask, i))
				printf ("sigismember for %i failed\n", i), status = 1;
		for (i = 1; i < NSIG; i += 2)
			if (!__sigismember (&mask, i))
				printf ("__sigismember for %i failed\n", i), status = 1;
		for (i = 2; i < NSIG; i += 2)
			if (__sigismember (&mask, i))
				printf ("__sigismember for %i failed\n", i), status = 1;
	}
	
	return 0;
}
