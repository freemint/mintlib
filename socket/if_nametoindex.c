#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

__typeof__(if_nametoindex) __if_nametoindex;

unsigned short 
__if_nametoindex(const char *name)
{
	struct ifreq ifr;
	int fd, r;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        __set_errno (ENODEV);
        return 0;
	}
	strlcpy(ifr.ifr_name, name, sizeof ifr.ifr_name);
	r = ioctl(fd, SIOCGIFINDEX, &ifr);
	close(fd);
	if(!r){
		return ifr.ifr_ifindex;
	}
	__set_errno (ENODEV);
	return 0;
}

weak_alias (__if_nametoindex, if_nametoindex)