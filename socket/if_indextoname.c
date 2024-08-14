#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

__typeof__(if_indextoname) __if_indextoname;

char *
__if_indextoname(unsigned short index, char name[IF_NAMESIZE])
{
	struct ifreq ifr;
	int fd, r;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){ 
        __set_errno (ENXIO);
        return NULL;
    }
	ifr.ifr_ifindex = index;
	r = ioctl(fd, SIOCGIFNAME_ETH, &ifr);
	close(fd);
    if(!r){
        return strncpy(name, ifr.ifr_name, IF_NAMESIZE);
    }
    __set_errno (ENXIO);
	return NULL;
}
weak_alias (__if_indextoname, if_indextoname)