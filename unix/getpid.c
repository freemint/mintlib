#include <osbind.h>
#include <unistd.h>
#include <mint/basepage.h>
#include <mint/mintbind.h>
#include <errno.h>

int
__getpid(void)
{
  	int r;
  	static short have_getpid = 1;
  
  	if (have_getpid) {
  		r = (int)Pgetpid();
		if (r == -ENOSYS)
			have_getpid = 0;
		else
			return r;
	}
	return ((int) ( ((long)_base) >> 8 ));
}

weak_alias (__getpid, getpid)
