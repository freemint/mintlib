/*
 * spawnxxx stuff for MiNT/TOS; written by Eric R. Smith, and
 * placed in the public domain
 */

#include <stdarg.h>
#include <process.h>
#include "lib.h"


int
spawnve(int mode, const char *path, char *const *argv, char *const *envp)
{
	return _spawnve(mode, path, argv, envp);
}

int
spawnv(int mode, const char *path, char *const *argv)
{
	return _spawnve(mode, path, argv, environ);
}

int
spawnle(int mode, const char *path, ...)
{
	va_list args;
	char	***envp;
	int	r;

	va_start(args, path);

	for (envp = (char ***) args ; *envp ; envp++)
		;
	r = _spawnve(mode, path, (char **)args, *(envp+1));
	va_end(args);
	return r;
}

int
spawnl(int mode, const char *path, ...)
{
	va_list args;
	int r;

	va_start(args, path);
	r = _spawnve(mode, path, (char **)args, environ);
	va_end(args);
	return r;
}
