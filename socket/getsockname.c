/*
 *	getsockname() emulation for MiNT-Net, (w) '93, kay roemer
 */

#include "socklib.h"
#ifdef KERNEL
#include "kerbind.h"
#else
#include <mintbind.h>
#endif
#include "sys/socket.h"
#include "mintsock.h"

#ifndef KERNEL
#include <support.h>
#include <limits.h>
#include "sys/un.h"
#define UN_OFFSET	((short)((struct sockaddr_un *)0)->sun_path)
#endif

#ifndef KERNEL
extern int errno;
#endif

int
getsockname (fd, addr, addrlen)
	int fd;
	struct sockaddr *addr;
	size_t *addrlen;
{
	struct getsockname_cmd cmd;
	short addrlen16;
	int r;
#ifndef KERNEL
	size_t oaddrlen = addrlen ? *addrlen : 0;
	extern int __libc_unix_names;
#endif

	if (addrlen) addrlen16 = (short)*addrlen;
	
	cmd.cmd =	GETSOCKNAME_CMD;
	cmd.addr =	addr;
	cmd.addrlen =	&addrlen16;
	
#ifdef KERNEL
	r = f_cntl (fd, (long)&cmd, SOCKETCALL);
#else
	r = Fcntl (fd, (long)&cmd, SOCKETCALL);
#endif
	if (addrlen) *addrlen = addrlen16;

#ifndef KERNEL
	if (!__libc_unix_names && addr && addrlen && addr->sa_family == AF_UNIX && r >= 0) {
		struct sockaddr_un *unp = (struct sockaddr_un *)addr;
		char name[sizeof (unp->sun_path)];
		extern int _sncpy (char *, const char *, size_t);

		if (addrlen16 > UN_OFFSET) {
			_dos2unx (unp->sun_path, name, PATH_MAX);
			*addrlen = UN_OFFSET + _sncpy (unp->sun_path, name,
				oaddrlen - UN_OFFSET);
		}
	}
#endif

#ifdef KERNEL
	return r;
#else
	if (r < 0) {
		errno = -r;
		return -1;
	}
	return 0;
#endif
}
