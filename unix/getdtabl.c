#include <stdio.h>
#include <mintbind.h>
#include <support.h>
#include <unistd.h>
#include <errno.h>

int
getdtablesize()
{
	int r;

	r = (int)Sysconf(_SC_OPEN_MAX);

	if (r == -ENOSYS)
		return FOPEN_MAX;
	return r;	
}
