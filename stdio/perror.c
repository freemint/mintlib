/* originally from Dale Schumacher's dLibs */

/*
 * standard "print error message" function
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>

void perror(msg)
	const char *msg;
	{
	if(msg && *msg)
		{
		fputs(msg, stderr);
		fputs(": ", stderr);
		}
	if((msg = strerror(errno)) != NULL)
		fputs(msg, stderr);
	fputs(".\n", stderr);
	}
