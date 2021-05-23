/* getifaddrs -- get names and addresses of all network interfaces
   Copyright (C) 2002-2021 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <ifaddrs.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>

#define ISLOOPBACK(p) ((p)->ifr_flags & IFF_LOOPBACK)

__typeof__(getifaddrs) __getifaddrs;

	
/* Create a linked list of `struct ifaddrs' structures, one for each
   network interface on the host machine.  If successful, store the
   list in *IFAP and return 0.  On errors, return -1 and set `errno'.  */
int __getifaddrs(struct ifaddrs **ifap)
{
	/* This implementation handles only IPv4 interfaces.
	   The various ioctls below will only work on an AF_INET socket.
	   Some different mechanism entirely must be used for IPv6.  */
	int fd;
	struct ifconf ifc;
	struct ifreq *ifr;
	struct ifreq *ibuf;
	struct ifaddrs **last;
	struct {
		struct ifaddrs ia;
		struct sockaddr addr;
		struct sockaddr netmask;
		struct sockaddr broadaddr;
	} *storage;
	int i, nifs;
	size_t namelen;
	char *names;
	
	*ifap = NULL;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
		return -1;

	ifc.ifc_len = 0;
	ifc.ifc_buf = NULL;
 	if (ioctl(fd, SIOCGIFCONF, (char *)&ifc) < 0 ||
	    ifc.ifc_len < (int)sizeof(struct ifreq))
	{
		close(fd);
		return -1;
	}
	nifs = (int)(ifc.ifc_len / sizeof(struct ifreq));
	ibuf = malloc(nifs * sizeof(*ibuf));
	if (ibuf == NULL)
	{
		close(fd);
		return -1;
	}
	ifc.ifc_len = nifs * sizeof(*ibuf);
	ifc.ifc_buf = (void *)ibuf;

 	if (ioctl(fd, SIOCGIFCONF, (char *)&ifc) < 0 ||
	    ifc.ifc_len < (int)sizeof(struct ifreq))
	{
		free(ibuf);
		close(fd);
		return -1;
	}
	nifs = (int)(ifc.ifc_len / sizeof(struct ifreq));

	namelen = 0;
	for (i = 0; i < nifs; i++)
		namelen += strlen(ibuf[i].ifr_name) + 1;
	
	storage = malloc((nifs * sizeof(*storage)) + namelen);
	if (storage == NULL)
	{
		free(ibuf);
		close(fd);
		return -1;
	}
	names = (char *)(storage + nifs);

	/* Now get the list of interfaces and each one's address.
	   Put it into the expected format and fill in the remaining details.  */
	last = ifap;
	for (i = 0; i < nifs; i++, storage++)
	{
		ifr = &ibuf[i];
		storage->ia.ifa_next = NULL;
		*last = &storage->ia;
		last = &(storage->ia.ifa_next);
		
		/* Now copy the information we already have from SIOCGIFCONF.  */
		storage->ia.ifa_name = names;
		strcpy(names, ifr->ifr_name);
		names += strlen(names);
		storage->addr = ifr->ifr_addr;
		storage->ia.ifa_addr = &storage->addr;

		/* The SIOCGIFCONF call filled in only the name and address.
		   Now we must also ask for the other information we need.  */

		if (ioctl(fd, SIOCGIFFLAGS, ifr) < 0)
			break;
		storage->ia.ifa_flags = ifr->ifr_flags;

		ifr->ifr_addr = storage->addr;

		if (ioctl(fd, SIOCGIFNETMASK, ifr) < 0)
		{
			storage->ia.ifa_netmask = NULL;
		} else
		{
			storage->ia.ifa_netmask = &storage->netmask;
			storage->netmask = ifr->ifr_netmask;
		}

		storage->ia.ifa_broadaddr = NULL;
		if (ifr->ifr_flags & IFF_BROADCAST)
		{
			ifr->ifr_addr = storage->addr;
			if (ioctl(fd, SIOCGIFBRDADDR, ifr) >= 0)
			{
				storage->ia.ifa_broadaddr = &storage->broadaddr;
				storage->broadaddr = ifr->ifr_broadaddr;
			}
		} else if (ifr->ifr_flags & IFF_POINTOPOINT)
		{
			ifr->ifr_addr = storage->addr;
			if (ioctl(fd, SIOCGIFDSTADDR, ifr) >= 0)
			{
				storage->ia.ifa_broadaddr = &storage->broadaddr;
				storage->broadaddr = ifr->ifr_dstaddr;
			}
		}
		storage[i].ia.ifa_data = NULL;	/* Nothing here for now.  */
	}
	free(ibuf);
	close(fd);

	if (i < nifs)					/* Broke out early on error.  */
	{
		freeifaddrs(*ifap);
		*ifap = NULL;
		return -1;
	}

	return 0;
}

weak_alias(__getifaddrs, getifaddrs)


__typeof__(freeifaddrs) __freeifaddrs;

void freeifaddrs(struct ifaddrs *ifa)
{
	free(ifa);
}

weak_alias(__freeifaddrs, freeifaddrs)
