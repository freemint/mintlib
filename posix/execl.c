/*
	execl for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include <unistd.h>

int
execl(const char *path, const char *arg, ...)
{
	return __execve(path, (char **) &arg, NULL);
}
