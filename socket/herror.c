/*
 * (c) 1994, Kay Roemer.
 */

#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>

extern const char *h_errlist[];
extern int h_nerr;

/*
 * herror --
 *	print the error indicated by the h_errno value.
 */
void
herror (const char *s)
{
	fprintf (stderr, "%s: %s.\n",
		(s && *s) ? s : "",
		((u_int)h_errno < h_nerr)
			? h_errlist[h_errno]
			: "Unknown error");
}
