/*
	execle for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include <stdarg.h>
#include <process.h>
#include <unistd.h>

int
execle (const char *path, const char *arg, ...)
{
	va_list ap;
	char **envp;

	va_start(ap, arg);
	while ((va_arg(ap, char *)) != NULL)
		;
	envp = va_arg(ap, char **);
	va_end(ap);

	return __execve(path, (char **) &arg, envp);
}
