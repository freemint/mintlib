/*
 * nanosleep implemented by Alan Hourihane <alanh@fairlite.co.uk>
 */

#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <time.h>

#include "lib.h"	/* __mint */

int __nanosleep64(const struct timespec64 *req, struct timespec64 *rem)
{
	__int32_t high;
	struct timespec req32;
	struct timespec rem32;
	int ret;

	high = req->tv_sec >> 32;
	if (high != 0)
	{
		__set_errno(EINVAL);
		return -1;
	}
	req32.tv_sec = req->tv_sec;
	req32.tv_nsec = req->tv_nsec;
	ret = nanosleep(&req32, &rem32);
	if (ret < 0 && errno == EINTR && rem)
	{
		rem->tv_sec = req32.tv_sec;
		rem->tv_nsec = req32.tv_nsec;
	}
	return ret;
}
