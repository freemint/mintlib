#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>

ssize_t
readv (s, iov, niov)
	int s;
	struct iovec *iov;
	ssize_t niov;
{
	struct msghdr m;
	char *p, *_p;
	long size, copy;
	int i;
	ssize_t r;

	m.msg_name = 0;
	m.msg_namelen = 0;
	m.msg_iov = (struct iovec*) iov;
	m.msg_iovlen = niov;
	m.msg_accrights = 0;
	m.msg_accrightslen = 0;

	r = recvmsg (s, &m, 0);
	if (r >= 0 || errno != -ENOSYS)
		return r;

	/*
	 * probably not a socket
	 */
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
	r = read (s, p, size);
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
