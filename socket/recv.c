/*
 *	recv() emulation for MiNT-Net, (w) '93, kay roemer
 */

#include <errno.h>
#include <stdlib.h>

#include <mint/mintbind.h>
#include <sys/socket.h>

#include "mintsock.h"
#include "sockets_global.h"


int
__recv (int fd, void *buf, ssize_t buflen, int flags)
{
	if (__libc_newsockets) {
		long r = Frecvfrom (fd, buf, buflen, flags, NULL, NULL);
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
		struct recv_cmd cmd;
		long r;
		
		cmd.cmd		= RECV_CMD;
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
weak_alias (__recv, recv)
