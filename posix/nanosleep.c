/*
 * nanosleep implemented by Alan Hourihane <alanh@fairlite.co.uk>
 */

#include <time.h>
#include <sys/time.h>
#include <errno.h>

enum { BILLION = 1000 * 1000 * 1000 };

int
nanosleep(const struct timespec *req, struct timespec *rem)
{
	struct timeval start, stop, remain, wait;
	int savederrno;
	int ret;

	if (req->tv_nsec < 0 || BILLION <= req->tv_nsec) {
		__set_errno(EINVAL);
		return -1;
	}

	wait.tv_sec = req->tv_sec;
	wait.tv_usec = (req->tv_nsec + 999) / 1000;
	if (wait.tv_usec == 1000000) {
		time_t t1 = wait.tv_sec + 1;
		if (t1 < wait.tv_sec)
			wait.tv_usec = 999999;
		else {
			wait.tv_sec = t1;
			wait.tv_usec = 0;
		}
	}

	gettimeofday(&start, NULL);

	ret = select(0, NULL, NULL, NULL, &wait);

	if (ret == 0)
		return 0;

	savederrno = errno;
	gettimeofday (&stop, NULL);

	remain.tv_sec = wait.tv_sec - (stop.tv_sec - start.tv_sec);
	remain.tv_usec = wait.tv_usec - (stop.tv_usec - start.tv_usec);
	remain.tv_sec += remain.tv_usec / 1000000L;
	remain.tv_usec %= 1000000L;

	TIMEVAL_TO_TIMESPEC(&remain, rem)

	errno = savederrno;

	return -1;
}
