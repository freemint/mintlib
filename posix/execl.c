/*
	execl for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include <stdarg.h>
#include <process.h>
#include <unistd.h>

#ifdef __STDC__
int execl(const char *path, ...)
#else
int execl(path)
	char	*path;
#endif
{
	va_list args;

	va_start(args, path);
	return execve (path, (char **)args, NULL);
}
