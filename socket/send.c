/*
 *	send() emulation for MiNT-Net, (w) '93, kay roemer
 */

#include "socklib.h"
#ifdef KERNEL
#include "kerbind.h"
#else
#include <mintbind.h>
#endif
#include <sys/types.h>
#include "sys/socket.h"
#include "mintsock.h"

#ifndef KERNEL
extern int errno;
#endif

int
send (fd, buf, buflen, flags)
	int fd;
	const void *buf;
	ssize_t buflen;
	int flags;
{
	struct send_cmd cmd;
	int r;

	cmd.cmd =	SEND_CMD;
	cmd.buf =	buf;
	cmd.buflen =	buflen;
	cmd.flags =	flags;

#ifdef KERNEL
	r = f_cntl (fd, (long)&cmd, SOCKETCALL);
#else
	r = Fcntl (fd, (long)&cmd, SOCKETCALL);
	if (r < 0) {
		errno = -r;
		return -1;
	}
#endif
	return r;
}
