/*
	execv for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include <process.h>
#include <unistd.h>

int
execv(path, argv)
	const char *path;
	char *const *argv;
{
	return execve (path, argv, NULL);
}

