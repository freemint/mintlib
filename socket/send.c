/*
 *	send() emulation for MiNT-Net, (w) '93, kay roemer
 */

#include <errno.h>
#include <stdlib.h>

#include <mint/mintbind.h>
#include <sys/socket.h>

#include "mintsock.h"
#include "sockets_global.h"


int
__send (int fd, const void *buf, ssize_t buflen, int flags)
{
	if (__libc_newsockets) {
		long r = Fsendto (fd, buf, buflen, flags, NULL, 0);
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
		struct send_cmd cmd;
		long r;
		
		cmd.cmd		= SEND_CMD;
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
weak_alias (__send, send)
