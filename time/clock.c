/* _clock -- return process time used so far, in units of CLK_TCK ticks
   per second (under TOS, 200 per second) */
/* written by ERS */

#include <time.h>
#include <mint/sysvars.h>

#include "lib.h"


clock_t
_clock(void)
{
	return (get_sysvar(_hz_200) - _starttime);
}

/* This next bit of nonsense is temporary...clock() should be fixed! */
strong_alias (_clock, clock)
