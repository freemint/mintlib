/*
 *	sendto() emulation for MiNT-Net, (w) '93, kay roemer
 */

#include "socklib.h"
#ifdef KERNEL
#include "kerbind.h"
#else
#include <mintbind.h>
#include <errno.h>
#endif
#include "sys/socket.h"
#include "mintsock.h"

#ifndef KERNEL
#include <limits.h>
#include <support.h>
#include <string.h>
#include "sys/un.h"
#define UN_OFFSET	((short)((struct sockaddr_un *)0)->sun_path)
#endif

#ifndef KERNEL
extern int errno;
#endif

int
sendto (fd, buf, buflen, flags, addr, addrlen)
	int fd;
	const void *buf;
	ssize_t buflen;
	int flags;
	const struct sockaddr *addr;
	int addrlen;
{
	struct sendto_cmd cmd;
	int r;
#ifndef KERNEL
	struct sockaddr_un un;
	extern int __libc_unix_names;

	if (!__libc_unix_names && addr && addr->sa_family == AF_UNIX) {
		struct sockaddr_un *unp = (struct sockaddr_un *)addr;

		if (addrlen <= UN_OFFSET || addrlen > sizeof (un)) {
			errno = EINVAL;
			return -1;
		}

		un.sun_family = AF_UNIX;
		_unx2dos (unp->sun_path, un.sun_path, PATH_MAX);
		un.sun_path[sizeof (un.sun_path) - 1] = '\0';
		cmd.addr =	(struct sockaddr *)&un;
		cmd.addrlen =	UN_OFFSET + strlen (un.sun_path);
	} else {
#endif
		cmd.addr =	addr;
		cmd.addrlen = 	(short)addrlen;
#ifndef KERNEL
	}
#endif
	cmd.cmd =	SENDTO_CMD;
	cmd.buf =	buf;
	cmd.buflen =	buflen;
	cmd.flags =	flags;

#ifdef KERNEL
	r = f_cntl (fd, (long)&cmd, SOCKETCALL);
#else
	r = Fcntl (fd, (long)&cmd, SOCKETCALL);
	if (r < 0) {
		errno = -r;
		return -1;
	}
#endif
	return r;
}
