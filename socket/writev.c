#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t
writev (s, iov, niov)
	int s;
	const struct iovec *iov;
	ssize_t niov;
{
	struct msghdr m;
	long size;
	char *p, *_p;
	int i;
	ssize_t r;

	m.msg_name = 0;
	m.msg_namelen = 0;
	m.msg_iov = (struct iovec*) iov;
	m.msg_iovlen = niov;
	m.msg_accrights = 0;
	m.msg_accrightslen = 0;

	r = sendmsg (s, &m, 0);
	if (r >= 0 || errno != ENOSYS)
		return r;

	/*
	 * probably not a socket
	 */
	for (i = size = 0; i < niov; ++i) {
		if (iov[i].iov_len >= 0)
			size += iov[i].iov_len;
		else {
			errno = EINVAL;
			return -1;
		}
	}
	if (!(p = _p = malloc (size))) {
		errno = ENOMEM;
		return -1;
	}
	for (i = 0; i < niov; ++i) {
		memcpy (p, iov[i].iov_base, iov[i].iov_len);
		p += iov[i].iov_len;
	}
	r = write (s, _p, size);
	free (_p);
	return r;	
}
