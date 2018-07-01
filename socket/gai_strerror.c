/*
 *	gai_strerror() emulation for MiNT-Net, (c) 2018, Thorsten Otto.
 */
#include "lib.h"
#include <netdb.h>
#include "sockets_global.h"

#ifndef _
# define _(x) x
# define N_(x) x
#endif

static struct
{
	int code;
	const char *msg;
} const gai_errlist[] =
{
	{ 0, N_("Success") },
	{ EAI_BADFLAGS, N_("Invalid value for ai_flags field") },
	{ EAI_NONAME, N_("Host or service not found") },
	{ EAI_AGAIN, N_("Temporary name service failure") },
	{ EAI_FAIL, N_("Non-recoverable name service failure") },
	{ EAI_NODATA, N_("No data for host name") },
	{ EAI_FAMILY, N_("Unsupported address family") },
	{ EAI_SOCKTYPE, N_("Unsupported socket type") },
	{ EAI_SERVICE, N_("Incompatible service for socket type") },
	{ EAI_ADDRFAMILY, N_("Address family for hostname not supported") },
	{ EAI_MEMORY, N_("Memory allocation failure") },
	{ EAI_SYSTEM, N_("System error") },
	{ EAI_OVERFLOW, N_("Buffer overflow") },
	{ EAI_INPROGRESS, N_("Processing request in progress") },
	{ EAI_NOTCANCELED, N_("Request not canceled") },
	{ EAI_ALLDONE, N_("All requests done") },
	{ EAI_INTR, N_("Interrupted by a signal") },
	{ EAI_IDN_ENCODE, N_("IDN encoding failed") },
	{ 0, NULL }
};

static const char gai_unknownerr[] = N_("Unrecognized error number");

/****************************************************************************
 * Converts an EAI_* error code into human readable english text.
 ****************************************************************************/
const char *__gai_strerror(int errnum)
{
	unsigned int i;

	for (i = 0; *gai_errlist[i].msg; i++)
		if (errnum == gai_errlist[i].code)
			return _(gai_errlist[i].msg);

	return _(gai_unknownerr);
}
weak_alias(__gai_strerror, gai_strerror)
