/*
 *	sendmsg() emulation for MiNT-Net, (w) '93, kay roemer
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
#include <string.h>
#include <support.h>
#include <limits.h>
#include "sys/un.h"
#define UN_OFFSET	((short)((struct sockaddr_un *)0)->sun_path)
#endif

#ifndef KERNEL
extern int errno;
#endif

int
sendmsg (fd, msg, flags)
	int fd;
	const struct msghdr *msg;
	int flags;
{
	struct sendmsg_cmd cmd;
	int r;
#ifndef KERNEL
	struct msghdr new_msg;
	struct sockaddr_un un, *unp = (struct sockaddr_un *)msg->msg_name;
	extern int __libc_unix_names;

	if (!__libc_unix_names && unp && unp->sun_family == AF_UNIX) {
		if (msg->msg_namelen <= UN_OFFSET ||
		    msg->msg_namelen > sizeof (un)) {
			errno = EINVAL;
			return -1;
		}

		un.sun_family = AF_UNIX;
		_unx2dos (unp->sun_path, un.sun_path, PATH_MAX);
		un.sun_path[sizeof (un.sun_path) - 1] = '\0';

		new_msg.msg_name = &un;
		new_msg.msg_namelen = UN_OFFSET + strlen (un.sun_path);
		new_msg.msg_iov = msg->msg_iov;
		new_msg.msg_iovlen = msg->msg_iovlen;
		new_msg.msg_accrights = msg->msg_accrights;
		new_msg.msg_accrightslen = msg->msg_accrightslen;
		
		cmd.msg = &new_msg;
	} else {
#endif
		cmd.msg = msg;
#ifndef KERNEL
	}
#endif
	cmd.cmd = SENDMSG_CMD;
	cmd.flags = flags;

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
