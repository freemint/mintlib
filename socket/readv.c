
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
__readv (int fd, struct iovec *iov, ssize_t niov)
{
	if (__libc_newsockets) {
		long r = Freadv (fd, iov, niov);
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
		
		r = recvmsg (fd, &m, 0);
		if (r >= 0 || errno != -ENOSYS)
			return r;
		
		{
			char *p, *_p;
			long size, copy;
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
			r = read (fd, p, size);
			if (r <= 0) {
				free (p);
				return r;
			}
			for (i = 0, size = r; size > 0; ++i) {
				copy = size > iov[i].iov_len ? iov[i].iov_len : size;
				memcpy (iov[i].iov_base, p, copy);
				p += copy;
				size -= copy;
			}
			free (_p);
			return r;
		}
	}
}
weak_alias (__readv, readv)
