/* _clock -- return process time used so far, in units of CLK_TCK ticks
   per second (under TOS, 200 per second) */
/* written by ERS */

#include <time.h>
#include <mint/sysvars.h>

#include "lib.h"

static clock_t _starttime;	/* 200 HZ tick when we started the program.  */

__attribute__((__constructor__))
static void init_clock(void)
{
	_starttime = get_sysvar (_hz_200);
}

clock_t
_clock(void)
{
	return (get_sysvar(_hz_200) - _starttime);
}

/* This next bit of nonsense is temporary...clock() should be fixed! */
strong_alias (_clock, clock)
