/*
	execl for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include <stdarg.h>
#include <process.h>
#include <unistd.h>

int
execl(const char *path, ...)
{
	va_list args;
	int r;

	va_start (args, path);
	r = __execve (path, (char **) args, NULL);
	va_end (args);

	return r;
}
