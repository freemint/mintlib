#include <stdio.h>
#include <stdlib.h>

static void goodbye (void);

int
main (int argc, char* argv[])
{
	if (atexit (goodbye) != 0) {
		perror ("atexit");
		return 1;
	}
	
	return 0;
}

static
void goodbye (void)
{
	printf ("Goodbye Johnny!\n");
}
