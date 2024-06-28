#include <ifaddrs.h>
#include <net/if.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	struct ifaddrs *ifap;
	struct ifaddrs *ifa;
	const char *addr;
	struct sockaddr_in *sa;
	char buf[1024];

	if (getifaddrs(&ifap) == -1)
	{
		perror("getifaddrs");
		return 1;
	}
	for (ifa = ifap; ifa; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr)
		{
			switch (ifa->ifa_addr->sa_family)
			{
			case AF_INET:
			case AF_INET6:
				sa = (struct sockaddr_in *) ifa->ifa_addr;
				addr = inet_ntop(ifa->ifa_addr->sa_family, &sa->sin_addr, buf, sizeof(buf));
				printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);
				break;
			}
		}

	}

	freeifaddrs(ifap);
	return 0;
}
