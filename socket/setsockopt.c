/*
 *	setsockopt() emulation for MiNT-Net, (w) '93, kay roemer
 */

#include <errno.h>

#include <mint/mintbind.h>
#include <sys/socket.h>

#include "mintsock.h"
#include "sockets_global.h"


int
__setsockopt (int fd, int level, int optname, void *optval, socklen_t optlen)
{
	if (__libc_newsockets) {
		long r = Fsetsockopt (fd, level, optname, optval, optlen);
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
		struct setsockopt_cmd cmd;
		long r;
		
		cmd.cmd		= SETSOCKOPT_CMD;
		cmd.level	= level;
		cmd.optname	= optname;
		cmd.optval	= optval;
		cmd.optlen	= optlen;
		
		r = Fcntl (fd, (long) &cmd, SOCKETCALL);
		if (r < 0) {
			__set_errno (-r);
			return -1;
		}
		return 0;
	}
}
weak_alias (__setsockopt, setsockopt)
