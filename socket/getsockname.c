/*
 *	getsockname() emulation for MiNT-Net, (w) '93, kay roemer
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
#error socklen_t is unsigned int, must be wrapped for the syscall
#endif


int
__getsockname (int fd, struct sockaddr *addr, socklen_t *addrlen)
{
	if (__libc_newsockets) {
		long r = Fgetsockname (fd, addr, addrlen);
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
		struct getsockname_cmd cmd;
		short addrlen16;
		long r;
		
		if (addrlen)
			addrlen16 = (short) *addrlen;
		
		cmd.cmd		= GETSOCKNAME_CMD;
		cmd.addr	= addr;
		cmd.addrlen	= &addrlen16;
		
		r = Fcntl (fd, (long) &cmd, SOCKETCALL);
		
		if (addrlen) {
			size_t oaddrlen;
			
			oaddrlen = *addrlen;
			*addrlen = addrlen16;
			
			if (!__libc_unix_names && addr && addr->sa_family == AF_UNIX && r >= 0) {
				struct sockaddr_un *unp = (struct sockaddr_un *)addr;
				char name[sizeof (unp->sun_path)];
				
				if (addrlen16 > UN_OFFSET) {
					_dos2unx (unp->sun_path, name, PATH_MAX);
					*addrlen = UN_OFFSET;
					*addrlen += _sncpy (unp->sun_path, name, oaddrlen - UN_OFFSET);
				}
			}
		}
		
		if (r < 0) {
			__set_errno (-r);
			return -1;
		}
		return 0;
	}
}
weak_alias (__getsockname, getsockname)
