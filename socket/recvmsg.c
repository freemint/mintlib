/*
 *	recvmsg() emulation for MiNT-Net, (w) '93, kay roemer
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
#include "sncpy.h"
#include "sockets_global.h"

#ifdef __MSHORT__
#error struct msghdr is not mshort clean, must be wrapped
#endif


int
__recvmsg (int fd, struct msghdr *msg, int flags)
{
	if (__libc_newsockets) {
		long r = Frecvmsg (fd, msg, flags);
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
		struct recvmsg_cmd cmd;
		struct sockaddr_un *unp = (struct sockaddr_un *) msg->msg_name;
		size_t oaddrlen = msg->msg_namelen;
		long r;
		
		cmd.cmd = RECVMSG_CMD;
		cmd.msg = msg;
		cmd.flags = flags;
		
		r = Fcntl (fd, (long) &cmd, SOCKETCALL);
		
		if (!__libc_unix_names && unp && unp->sun_family == AF_UNIX && r >= 0) {
			char name[sizeof (unp->sun_path)];
			
			if (msg->msg_namelen > UN_OFFSET) {
				_dos2unx (unp->sun_path, name, PATH_MAX);
				msg->msg_namelen = UN_OFFSET;
				msg->msg_namelen += _sncpy (unp->sun_path, name, oaddrlen - UN_OFFSET);
			}
		}
		
		if (r < 0) {
			__set_errno (-r);
			return -1;
		}
		return r;
	}
}
weak_alias (__recvmsg, recvmsg)
