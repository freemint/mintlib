/* by ERS, modified by entropy */

#include <signal.h>
#include <stdlib.h>

__EXITING
abort (void)
{
	raise (SIGABRT);
	exit (127);
}
