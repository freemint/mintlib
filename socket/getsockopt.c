/*
 *	getsockopt() emulation for MiNT-Net, (w) '93, kay roemer
 */

#include <errno.h>

#include <mint/mintbind.h>
#include <sys/socket.h>

#include "mintsock.h"
#include "sockets_global.h"

#ifdef __MSHORT__
#error socklen_t is unsigned int, must be wrapped for the syscall
#endif


int
__getsockopt (int fd, int level, int optname, void *optval, socklen_t *optlen)
{
	if (__libc_newsockets) {
		long r = Fgetsockopt (fd, level, optname, optval, optlen);
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
		struct getsockopt_cmd cmd;
		long optlen32;
		int r;
		
		if (optlen)
			optlen32 = *optlen;
		
		cmd.cmd		= GETSOCKOPT_CMD;
		cmd.level	= level;
		cmd.optname	= optname;
		cmd.optval	= optval;
		cmd.optlen	= &optlen32;
		
		r = Fcntl (fd, (long) &cmd, SOCKETCALL);
		
		if (optlen)
			*optlen = optlen32;
		
		if (r < 0) {
			__set_errno (-r);
			return -1;
		}
		return 0;
	}
}
weak_alias (__getsockopt, getsockopt)
