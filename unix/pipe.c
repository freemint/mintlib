/*
 * pipe: create a pipe
 * works only under MiNT
 */

#include <errno.h>
#include <unistd.h>
#include <mint/mintbind.h>
#include "lib.h"

int
__pipe (int *fd)
{
	short mint_handle[2];
	long r;

	r = Fpipe(mint_handle);
	if (r < 0) {
		__set_errno (-r);
		return -1;
	}
	fd[0] = mint_handle[0];
	fd[1] = mint_handle[1];
	/* fix the case `isatty() called before and not closed thru close()' */
	if (__OPEN_INDEX(fd[0]) < __NHANDLES)
		__open_stat[__OPEN_INDEX(fd[0])].status = FH_UNKNOWN;
	if (__OPEN_INDEX(fd[1]) < __NHANDLES)
		__open_stat[__OPEN_INDEX(fd[1])].status = FH_UNKNOWN;
	return 0;
}
weak_alias (__pipe, pipe)
