/*
 *	sendmsg() emulation for MiNT-Net, (w) '93, kay roemer
 */

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <support.h>

#include <mint/mintbind.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "mintlib/lib.h"
#include "mintsock.h"
#include "sockets_global.h"

#ifdef __MSHORT__
#error struct msghdr is not mshort clean, must be wrapped
#endif


int
__sendmsg (int fd, const struct msghdr *msg, int flags)
{
	if (__libc_newsockets) {
		long r = Fsendmsg (fd, msg, flags);
		if (r != -ENOSYS) {
			if (r < 0) {
				__set_errno (-r);
				return -1;
			}
			return r;
		} else
			__libc_newsockets = 0;
	}
	
	{
		struct sendmsg_cmd cmd;
		struct msghdr new_msg;
		struct sockaddr_un un, *unp = (struct sockaddr_un *) msg->msg_name;
		long r;
		
		if (!__libc_unix_names && unp && unp->sun_family == AF_UNIX) {
			if (msg->msg_namelen <= UN_OFFSET || msg->msg_namelen > sizeof (un)) {
				__set_errno (EINVAL);
				return -1;
			}
			
			un.sun_family = AF_UNIX;
			_unx2dos (unp->sun_path, un.sun_path, PATH_MAX);
			un.sun_path[sizeof (un.sun_path) - 1] = '\0';
			
			new_msg.msg_name = &un;
			new_msg.msg_namelen = UN_OFFSET + strlen (un.sun_path);
			new_msg.msg_iov = msg->msg_iov;
			new_msg.msg_iovlen = msg->msg_iovlen;
			new_msg.msg_control = msg->msg_control;
			new_msg.msg_controllen = msg->msg_controllen;
			
			cmd.msg = &new_msg;
		} else {
			cmd.msg = msg;
		}
		cmd.cmd = SENDMSG_CMD;
		cmd.flags = flags;
		
		r = Fcntl (fd, (long) &cmd, SOCKETCALL);
		if (r < 0) {
			__set_errno (-r);
			return -1;
		}
		return r;
	}
}
weak_alias (__sendmsg, sendmsg)
