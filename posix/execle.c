/*
	execle for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include <stdarg.h>
#include <process.h>
#include <unistd.h>

int
execle (const char *path, ...)
{
	va_list args;
	char ***envp;
	int r;

	va_start (args, path);

	for (envp = (char ***) args ; *envp ; envp++)
		;

	r = __execve (path, (char **) args, *(envp+1));

	va_end (args);

	return r;
}
