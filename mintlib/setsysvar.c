
#include <support.h>
#include <mint/mintbind.h>
#include <mint/ssystem.h>

#include "lib.h"

void
set_sysvar_to_long (void *var, long val)
{
	if(__has_no_ssystem) {
		long save_ssp;

    		save_ssp = (long) Super((void *) 0L);
    		*((volatile long *)var) = val;
    		(void)SuperToUser((void *) save_ssp);
	}
	else
		(void) Ssystem (S_SETLVAL, var, val); /* note: root only! */
}
