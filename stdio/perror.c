/* originally from Dale Schumacher's dLibs */

/*
 * standard "print error message" function
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>

void perror(const char *msg)
{
	const char *error = strerror(errno);

	if (msg && *msg)
	{
		fputs(msg, stderr);
		fputs(": ", stderr);
	}
	if (error != NULL)
		fputs(error, stderr);
	fputs("\n", stderr);
}
