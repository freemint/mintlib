/*
	execve for MiNT/TOS; written by Eric R. Smith, and
	placed in the public domain
*/

#include <process.h>
#include <unistd.h>
#include "lib.h"

int
__execve (const char *path, char *const *argv, char *const *envp)
{
	return _spawnve (P_OVERLAY, path, argv, envp);
}
weak_alias (__execve, execve)
