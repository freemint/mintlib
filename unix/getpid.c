#include <osbind.h>
#include <unistd.h>
#include <basepage.h>
#include <mintbind.h>
#include <errno.h>

int
__getpid()
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
