#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netdb.h>


int ether_hostton(const char *hostname, struct ether_addr *e)
{
	FILE *f;
	char *p;
	char *cp;
	char tryname[MAXHOSTNAMELEN + 1];
	char line[BUFSIZ + 1];
	
	f = fopen(_PATH_ETHERS, "r");
	if (f == NULL)
		return -1;

	for (;;)
	{
		p = fgets(line, BUFSIZ, f);
		if (p == NULL)
			break;
		if (*p != '#')
		{
			cp = strpbrk(p, "#\n");
			if (cp != NULL)
			{
				*cp = '\0';
				if (ether_line(p, e, tryname) == 0 && strcmp(hostname, tryname) == 0)
				{
					fclose(f);
					return 0;
				}
			}
		}
	}
	fclose(f);
	__set_errno(ENOENT);
	return -1;
}
