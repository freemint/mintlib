/*
 *	sendto() emulation for MiNT-Net, (w) '93, kay roemer
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


int
__sendto (int fd, const void *buf, ssize_t buflen, int flags, const struct sockaddr *addr, socklen_t addrlen)
{
	if (__libc_newsockets) {
		long r = Fsendto (fd, buf, buflen, flags, addr, addrlen);
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
		struct sendto_cmd cmd;
		struct sockaddr_un un;
		long r;
		
		if (!__libc_unix_names && addr && addr->sa_family == AF_UNIX) {
			struct sockaddr_un *unp = (struct sockaddr_un *) addr;
			
			if (addrlen <= UN_OFFSET || addrlen > sizeof (un)) {
				__set_errno (EINVAL);
				return -1;
			}
			
			un.sun_family = AF_UNIX;
			_unx2dos (unp->sun_path, un.sun_path, PATH_MAX);
			un.sun_path[sizeof (un.sun_path) - 1] = '\0';
			
			cmd.addr = (struct sockaddr *) &un;
			cmd.addrlen = UN_OFFSET + strlen (un.sun_path);
		} else {
			cmd.addr = addr;
			cmd.addrlen = (short) addrlen;
		}
		
		cmd.cmd		= SENDTO_CMD;
		cmd.buf		= buf;
		cmd.buflen	= buflen;
		cmd.flags	= flags;
		
		r = Fcntl (fd, (long) &cmd, SOCKETCALL);
		if (r < 0) {
			__set_errno (-r);
			return -1;
		}
		return r;
	}
}
weak_alias (__sendto, sendto)
