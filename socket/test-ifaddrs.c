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
	struct sockaddr_in *sa;
	char *addr;

	if (getifaddrs(&ifap) == -1)
	{
		perror("getifaddrs");
		return 1;
	}
	for (ifa = ifap; ifa; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET)
		{
			sa = (struct sockaddr_in *) ifa->ifa_addr;
			addr = inet_ntoa(sa->sin_addr);
			printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);
		}

	}

	freeifaddrs(ifap);
	return 0;
}
