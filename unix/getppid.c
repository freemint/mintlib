
#include <errno.h>
#include <unistd.h>
#include <mint/basepage.h>
#include <mint/mintbind.h>

int
__getppid (void)
{
	static short have_getppid = 1;

	if (have_getppid) {
		long r;
		
		r = Pgetppid ();
		if (r == -ENOSYS)
			have_getppid = 0;
		else
			return (int) r;
	}
	
	return (int)(((long)(_base->p_parent)) >> 8);
}
weak_alias (__getppid, getppid)
