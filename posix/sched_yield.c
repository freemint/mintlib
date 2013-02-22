/*
 * sched_yield implemented by Alan Hourihane <alanh@fairlite.co.uk>
 */
#include <mint/mintbind.h>
#include <errno.h>
#include <sched.h>

int 
sched_yield (void)
{
	int y;

	y = Syield();
	if (y < 0) {
		__set_errno(-y);
		return -1;
	}

	return 0;
}
