/* usleep -- sleep for a specified number of microSecond */
/* written by Eric R. Smith and placed in the public domain */
/* extensively rehacked by entropy for mint >= 0.95, still public domain */

#include <errno.h>
#include <time.h>
#include <mint/mintbind.h>

#define USEC_PER_TICK (1000000L / ((unsigned long)CLOCKS_PER_SEC))
#define	USEC_TO_CLOCK_TICKS(us)	((us) / USEC_PER_TICK )

clock_t _clock (void);

/*
 * Sleep for usec microSeconds 
 * the actual suspension time can be arbitrarily longer
 *
 */
void
usleep (unsigned long usec)
{
	long stop;
	int r = -ENOSYS;

	if (usec >= 1000)
		r = Fselect((unsigned)(usec/1000), 0L, 0L, 0L);

	if (r == -ENOSYS) {
		stop = _clock() + USEC_TO_CLOCK_TICKS(usec);
		while (_clock() < stop)
			;
	}
}
