#include <osbind.h>
#include <unistd.h>
#include <mint/basepage.h>
#include <mint/mintbind.h>
#include <errno.h>

int
__getppid()
{
	long r;
	static short have_getppid = 1;

	if (have_getppid) {
		r = Pgetppid();
		if (r == -ENOSYS)
			have_getppid = 0;
		else
			return (int)r;
	}
	return (int)(((long)(_base->p_parent)) >> 8);
}

weak_alias (__getppid, getppid)
