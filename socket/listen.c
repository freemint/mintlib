/*
 *	listen() emulation for MiNT-Net, (w) '93, kay roemer.
 */

#include <errno.h>

#include <mint/mintbind.h>
#include <sys/socket.h>

#include "mintsock.h"
#include "sockets_global.h"


int
__listen (int fd, int backlog)
{
	if (__libc_newsockets) {
		long r = Flisten (fd, backlog);
		if (r != -ENOSYS) {
			if (r < 0) {
				__set_errno (-r);
				return -1;
			}
			return 0;
		} else
			__libc_newsockets = 0;
	}
	
	{
		struct listen_cmd cmd;
		long r;
		
		cmd.cmd		= LISTEN_CMD;
		cmd.backlog	= backlog;
		
		r = Fcntl (fd, (long) &cmd, SOCKETCALL);
		if (r < 0) {
			__set_errno (-r);
			return -1;
		}
		return 0;
	}
}
weak_alias (__listen, listen)
