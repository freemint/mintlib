/*
	spawnxxx stuff for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include	<stdarg.h>
#include	<process.h>

extern char **environ;

int
spawnve(mode, path, argv, envp)
	int	mode;
	const char *path;
	char	*const *argv;
	char	*const *envp;
{
	return _spawnve(mode, path, argv, envp);
}

int
spawnv(mode, path, argv)
	int mode;
	const char *path;
	char *const *argv;
{
	return _spawnve(mode, path, argv, environ);
}

#ifdef __STDC__
int spawnle(int mode, const char *path, ...)
#else
int spawnle(mode, path)
	int	mode;
	char	*path;
#endif
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

#ifdef __STDC__
int spawnl(int mode, const char *path, ...)
#else
int spawnl(mode, path)
	int	mode;
	char	*path;
#endif
{
	va_list args;
	int r;

	va_start(args, path);
	r = _spawnve(mode, path, (char **)args, environ);
	va_end(args);
	return r;
}
