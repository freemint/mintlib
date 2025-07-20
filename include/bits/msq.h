/* Copyright (C) 1995, 1997, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#ifndef _SYS_MSG_H
#error "Never use <bits/msq.h> directly; include <sys/msg.h> instead."
#endif

#ifndef _BITS_TYPES_H
# include <bits/types.h>
#endif

/* Define options for message queue functions.  */
#define MSG_NOERROR	010000	/* no error if message is too big */

/* Types used in the structure definition.  */
typedef unsigned short int msgqnum_t;
typedef unsigned short int msglen_t;


/* Structure of record for one message inside the kernel.
   The type `struct __msg' is opaque.  */
struct msqid_ds
{
  struct ipc_perm msg_perm;	/* structure describing operation permission */
#ifdef __USE_TIME_BITS64
  __time64_t msg_stime;		/* time of last msgsnd command */
  __time64_t msg_rtime;		/* time of last msgrcv command */
  __time64_t msg_ctime;		/* time of last change */
#else
  __int32_t __msg_stime_high;
  __time_t msg_stime;		/* time of last msgsnd command */
  __int32_t __msg_rtime_high;
  __time_t msg_rtime;		/* time of last msgrcv command */
  __int32_t __msg_ctime_high;
  __time_t msg_ctime;		/* time of last change */
#endif
  size_t __msg_cbytes;		/* current number of bytes on queue */
  msgqnum_t msg_qnum;		/* number of messages currently on queue */
  msglen_t msg_qbytes;		/* max number of bytes allowed on queue */
  __pid_t msg_lspid;		/* pid of last msgsnd() */
  __pid_t msg_lrpid;		/* pid of last msgrcv() */
  unsigned long int __unused3;
  unsigned long int __unused4;
};
