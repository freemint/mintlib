/*
 *	socketpair() emulation for MiNT-Net, (w) '93, kay roemer.
 */

#include <errno.h>
#include <fcntl.h>

#include <mint/mintbind.h>
#include <sys/socket.h>

#include "mintsock.h"
#include "sockets_global.h"


int
__socketpair (int domain, int type, int proto, int fds[2])
{
	if (__libc_newsockets) {
		short _fds[2];
		long r = Fsocketpair (domain, type, proto, _fds);
		if (r != -ENOSYS) {
			if (r < 0) {
				__set_errno (-r);
				return -1;
			}
			fds[0] = _fds[0];
			fds[1] = _fds[1];
			return 0;
		} else
			__libc_newsockets = 0;
	}
	
	{
		struct socketpair_cmd cmd;
		int sockfd1, sockfd2;
		
		sockfd1 = Fopen (SOCKDEV, O_RDWR);
		if (sockfd1 < 0) {
			__set_errno (-sockfd1);
			return -1;
		}
		
		cmd.cmd		= SOCKETPAIR_CMD;
		cmd.domain	= domain;
		cmd.type	= type;
		cmd.protocol	= proto;
		
		sockfd2 = Fcntl (sockfd1, (long) &cmd, SOCKETCALL);
		if (sockfd2 < 0) {
			__set_errno (-sockfd2);
			Fclose (sockfd1);
			return -1;
		}
		
		fds[0] = sockfd1;
		fds[1] = sockfd2;
		
		return 0;
	}
}
weak_alias (__socketpair, socketpair)
