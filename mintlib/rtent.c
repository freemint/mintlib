/*
 * Routing table access functions for MintNet. (w) 1994 Kay Roemer.
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/route.h>
#include "rtent.h"

#define _PATH_DEV_ROUTE	"/dev/route"

struct route_info {
	char		nif[IFNAMSIZ];
	struct rtentry	rt;
};

static int rtfd = -1;
static struct route_info rtent;

void
setrtent (void)
{
	if (rtfd < 0) {
		rtfd = open (_PATH_DEV_ROUTE, O_RDONLY);
	}
}

void
endrtent (void)
{
	if (rtfd >= 0)
		close (rtfd);
	rtfd = -1;
}

struct rtentry *
getrtent (void)
{
	int r;

	if (rtfd < 0)
		return 0;
	r = read (rtfd, &rtent, sizeof (rtent));
	if (r != sizeof (rtent))
		return 0;
	return &rtent.rt;
}
