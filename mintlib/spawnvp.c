/* spawnvp, spawnlp: try to execute a program on the default system
   execution path. WARNING: the current directory is always searched
   first.

   Written by Eric R. Smith and placed in the public domain.

   Rehacked by Uwe Ohse, 3.5.93: uses buffindfile

*/
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <stdarg.h>
#include <errno.h>
#include <support.h>
#include <limits.h>

static char const *const extensions[] = { "ttp", "prg", "tos", NULL };

#ifdef __STDC__
int spawnvp(int mode, const char *name, char *const *argv)
#else
int spawnvp(mode, name, argv) int mode; char *name; char **argv;
#endif
{
	const char *execname;
      char buffer[PATH_MAX];
      execname = _buffindfile(name, getenv("PATH"), extensions,buffer);
	if (!execname) {
		__set_errno (ENOENT);
		return -1;		/* file not found */
	}
	return spawnve(mode, execname, argv, (char **)NULL);
}

#ifdef __STDC__
int spawnlp(int mode, const char *name, ...)
#else
int spawnlp(mode, name) int mode; char *name;
#endif
{
	va_list args;
	int r;

	va_start(args, name);
	r = spawnvp(mode, name, (char **)args);
	va_end(args);
	return r;
}
