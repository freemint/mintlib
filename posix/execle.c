/*
	execle for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include <stdarg.h>
#include <process.h>
#include <unistd.h>

#ifdef __STDC__
int execle(const char *path, ...)
#else
int execle(path)
	char	*path;
#endif
{
	va_list args;
	char	***envp;

	va_start(args, path);

	for (envp = (char ***) args ; *envp ; envp++)
		;
	return execve(path, (char **)args, *(envp+1));
}
