/* getrusage emulation for MiNT, 64bit version */

#include <compiler.h>
#include <osbind.h>
#include <mintbind.h>
#include <time.h>
#include <resource.h>
#include <errno.h>
#include <string.h>

#include "lib.h"

int __getrusage64(__rusage_who_t which, struct rusage64 *data)
{
	struct rusage data32;
	int r;

	r = getrusage(which, &data32);
	if (r == 0)
	{
		__rusage_to_rusage64(data, &data32);
	}
	return r;
}
