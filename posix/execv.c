/*
	execv for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include <process.h>
#include <unistd.h>

int
execv (const char *path, char *const *argv)
{
	return __execve (path, argv, NULL);
}
