
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <mint/mintbind.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "sockets_global.h"


ssize_t
__writev (int fd, const struct iovec *iov, ssize_t niov)
{
	if (__libc_newsockets) {
		long r = Fwritev (fd, iov, niov);
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
		struct msghdr m;
		ssize_t r;
		
		m.msg_name = 0;
		m.msg_namelen = 0;
		m.msg_iov = (struct iovec*) iov;
		m.msg_iovlen = niov;
		m.msg_control = 0;
		m.msg_controllen = 0;
		
		r = sendmsg (fd, &m, 0);
		if (r >= 0 || errno != ENOSYS)
			return r;
		
		{
			long size;
			char *p, *_p;
			int i;
			
			for (i = size = 0; i < niov; ++i) {
				if (iov[i].iov_len >= 0)
					size += iov[i].iov_len;
				else {
					__set_errno (EINVAL);
					return -1;
				}
			}
			if (!(p = _p = malloc (size))) {
				__set_errno (ENOMEM);
				return -1;
			}
			for (i = 0; i < niov; ++i) {
				memcpy (p, iov[i].iov_base, iov[i].iov_len);
				p += iov[i].iov_len;
			}
			r = write (fd, _p, size);
			free (_p);
			return r;
		}
	}
}
weak_alias (__writev, writev)
