
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

#include "lib.h"

extern uid_t __uid;

uid_t
__getuid (void)
{
	if (__mint)
		return Pgetuid ();
	else
		return __uid;
}
weak_alias (__getuid, getuid)
