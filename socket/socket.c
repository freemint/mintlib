/*
 *	socket() emulation for MiNT-Net, (w) '93, kay roemer.
 */

#include <errno.h>
#include <fcntl.h>

#include <mint/mintbind.h>
#include <sys/socket.h>

#include "mintsock.h"
#include "sockets_global.h"


int
__socket (int domain, int type, int proto)
{
	if (__libc_newsockets) {
		long r = Fsocket (domain, type, proto);
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
		struct socket_cmd cmd;
		int sockfd, r;
		
		sockfd = Fopen (SOCKDEV, O_RDWR);
		if (sockfd < 0) {
			__set_errno (-sockfd);
			return -1;
		}
		
		cmd.cmd		= SOCKET_CMD;
		cmd.domain	= domain;
		cmd.type	= type;
		cmd.protocol	= proto;
		
		r = Fcntl (sockfd, (long) &cmd, SOCKETCALL);
		if (r < 0) {
			__set_errno (-r);
			Fclose (sockfd);
			return -1;
		}
		
		return sockfd;
	}
}
weak_alias (__socket, socket)
