/*
 *	recvmsg() emulation for MiNT-Net, (w) '93, kay roemer
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
recvmsg (fd, msg, flags)
	int fd;
	struct msghdr *msg;
	int flags;
{
	struct recvmsg_cmd cmd;
	int r;
#ifndef KERNEL
	struct sockaddr_un *unp = (struct sockaddr_un *)msg->msg_name;
	size_t oaddrlen = msg->msg_namelen;
	extern int __libc_unix_names;
#endif

	cmd.cmd = RECVMSG_CMD;
	cmd.msg = msg;
	cmd.flags = flags;

#ifdef KERNEL
	r = f_cntl (fd, (long)&cmd, SOCKETCALL);
#else
	r = Fcntl (fd, (long)&cmd, SOCKETCALL);
#endif
	
#ifndef KERNEL
	if (!__libc_unix_names && unp && unp->sun_family == AF_UNIX && r >= 0) {
		char name[sizeof (unp->sun_path)];
		extern int _sncpy (char *, const char *, size_t);
		
		if (msg->msg_namelen > UN_OFFSET) {
			_dos2unx (unp->sun_path, name, PATH_MAX);
			msg->msg_namelen = UN_OFFSET + _sncpy (unp->sun_path,
				name, oaddrlen - UN_OFFSET);
		}
	}
#endif

#ifndef KERNEL
	if (r < 0) {
		errno = -r;
		return -1;
	}
#endif
	return r;
}
