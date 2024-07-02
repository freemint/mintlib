#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netdb.h>


int ether_ntohost(char *hostname, const struct ether_addr *e)
{
	FILE *f; 
	char *p;
	char *cp;
	struct ether_addr tryaddr;
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
				if (ether_line(p, &tryaddr, hostname) == 0 &&
				    memcmp(&tryaddr, e, sizeof tryaddr) == 0)
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
