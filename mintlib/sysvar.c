
#include <support.h>
#include <mint/mintbind.h>
#include <mint/ssystem.h>

#include "lib.h"


long
get_sysvar (void *var)
{
	if(__has_no_ssystem) {
		long save_ssp;
		long ret;

    		save_ssp = (long) Super((void *) 0L);

		/* note: dont remove volatile, otherwise gcc will reorder these
		 * statements and we get bombs */
    		ret = *((volatile long *)var);

    		(void)Super((void *) save_ssp);

    		return ret;
	}
	else
		return Ssystem (S_GETLVAL, var, NULL);
}

void
set_sysvar_to_long (void *var, long val)
{
	if(__has_no_ssystem) {
		long save_ssp;

    		save_ssp = (long) Super((void *) 0L);
    		*((volatile long *)var) = val;
    		(void)Super((void *) save_ssp);
	}
	else
		(void) Ssystem (S_SETLVAL, var, val); /* note: root only! */
}
