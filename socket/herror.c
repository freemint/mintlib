/*
 * herror() for Mint-Net, (w) 1994, Kay Roemer.
 */

#include "socklib.h"
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>

char	*h_errlist[] = {
	"Error 0",
	"Unknown host",				/* 1 HOST_NOT_FOUND */
	"Host name lookup failure",		/* 2 TRY_AGAIN */
	"Unknown server error",			/* 3 NO_RECOVERY */
	"No address associated with name",	/* 4 NO_ADDRESS */
};
int	h_nerr = { sizeof (h_errlist)/sizeof (h_errlist[0]) };

extern int	h_errno;

void
herror (s)
	const char *s;
{
	fprintf (stderr, "%s: %s.\n",
		(s && *s) ? s : "",
		((u_int)h_errno < h_nerr)
			? h_errlist[h_errno]
			: "Unknown error");
}
