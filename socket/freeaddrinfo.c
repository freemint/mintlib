/*
 *	freeaddrinfo() emulation for MiNT-Net, (c) 2018, Thorsten Otto.
 */
#include "lib.h"
#include <netdb.h>
#include "sockets_global.h"
#include <stdlib.h>

void __freeaddrinfo(struct addrinfo *ai)
{
	struct addrinfo *p;

	while (ai != NULL)
	{
		p = ai;
		ai = ai->ai_next;
		free(p);
    }
}
weak_alias(__freeaddrinfo, freeaddrinfo)
