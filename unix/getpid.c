
#include <errno.h>
#include <unistd.h>
#include <mint/basepage.h>
#include <mint/mintbind.h>

int
__getpid (void)
{
	static short have_getpid = 1;

	if (have_getpid) {
		long r;
		
		r = Pgetpid ();
		if (r == -ENOSYS)
			have_getpid = 0;
		else
			return (int) r;
	}
	return ((int) (((long) _base) >> 8 ));
}
weak_alias (__getpid, getpid)
