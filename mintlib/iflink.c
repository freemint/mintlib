/*
 * MiNT-Net specific functions for linking tty devices to network inter-
 * faces.
 * (w) '94, Kay Roemer <roemer@rbi.informatik.uni-frankfurt.de>.
 */

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sockios.h>
#include <netinet/in.h>
#include <net/if.h>
#include <mint/iflink.h>

#include <limits.h>
#include "lib.h" /* _unx2dos */

/*
 * link device to network interface.
 */
int
if_link (device, ifname)
	char *device, *ifname;
{
	struct iflink ifl;
	int sockfd;
	long r;

	sockfd = socket (PF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		return -1;
	}
	_unx2dos (device, ifl.device, PATH_MAX);
	strncpy (ifl.ifname, ifname, sizeof (ifl.ifname));
	r = ioctl (sockfd, SIOCSIFLINK, &ifl);
	if (r < 0) {
		close (sockfd);
		return -1;
	}
	close (sockfd);
	strncpy (ifname, ifl.ifname, sizeof (ifl.ifname));
	return 0;
}

/*
 * Get interface link level flags
 */
int
if_getlnkflags (ifname, flags)
	char *ifname;
	short *flags;
{
	struct ifreq ifr;
	int sock;

	sock = socket (PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		return -1;
	}
	strcpy (ifr.ifr_name, ifname);
	if (ioctl (sock, SIOCGLNKFLAGS, &ifr) < 0) {
		close (sock);
		return -1;
	}
	*flags = ifr.ifr_flags;
	close (sock);
	return 0;
}

/*
 * Set interface link level flags
 */
int
if_setlnkflags (ifname, flags)
	char *ifname;
	short flags;
{
	struct ifreq ifr;
	int sock;

	sock = socket (PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		return -1;
	}
	strcpy (ifr.ifr_name, ifname);
	ifr.ifr_flags = flags;
	if (ioctl (sock, SIOCSLNKFLAGS, &ifr) < 0) {
		close (sock);
		return -1;
	}
	close (sock);
	return 0;
}

/*
 * Get interface flags
 */
int
if_getifflags (ifname, flags)
	char *ifname;
	short *flags;
{
	struct ifreq ifr;
	int sock;

	sock = socket (PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		return -1;
	}
	strcpy (ifr.ifr_name, ifname);
	if (ioctl (sock, SIOCGIFFLAGS, &ifr) < 0) {
		close (sock);
		return -1;
	}
	*flags = ifr.ifr_flags;
	close (sock);
	return 0;
}

/*
 * Set interface link level flags
 */
int
if_setifflags (ifname, flags)
	char *ifname;
	short flags;
{
	struct ifreq ifr;
	int sock;

	sock = socket (PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		return -1;
	}
	strcpy (ifr.ifr_name, ifname);
	ifr.ifr_flags = flags;
	if (ioctl (sock, SIOCSIFFLAGS, &ifr) < 0) {
		close (sock);
		return -1;
	}
	close (sock);
	return 0;
}
