/*  time.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#ifndef N_
# define N_(String) String
#endif

#ifndef _
# define _(String) N_(String)
#endif

static char const unknown_error[] = N_("Unknown error");

const char* const _sys_errlist[] = {
  N_("Success"),			/* 0 */
  N_("Generic Error"),			/* 1 - EERROR */
  N_("Device or resource busy"),	/* 2 - EBUSY */
  N_("Unknown command"),		/* 3 - EUKCMD */
  N_("CRC error"),			/* 4 - ECRC */
  N_("Invalid request descriptor"),	/* 5 - EBADR */
  N_("Illegal seek"),			/* 6 - ESPIPE */
  N_("Wrong medium type"),		/* 7 - EMEDIUMTYPE */
  N_("Sector not found"),		/* 8 - ESECTOR */
  N_("Out of paper"),			/* 9 - EPAPER */
  N_("Write fault"),			/* 10 - EWRITE */
  N_("Read fault"),			/* 11 - EREAD */
  N_("General mishap"),			/* 12 - EGENERIC */
  N_("Read-only file system"),		/* 13 - EROFS */
  N_("Media changed"),			/* 14 - ECHMEDIA */
  N_("No such device"),			/* 15 - ENODEV */
  N_("Bad sectors found"),		/* 16 - EBADSEC */
  N_("No medium found"),		/* 17 - ENOMEDIUM */
  N_("Insert media"),			/* 18 - EINSERT */
  N_("Drive not responding"),		/* 19 - EDRVNRSP */
  N_("No such process"),		/* 20 - ESRCH */
  N_("No child process"),		/* 21 - ECHILD */
  N_("Resource deadlock avoided"),	/* 22 - EDEADLK */
  N_("Block device required"),		/* 23 - ENOTBLK */
  N_("Is a directory"),			/* 24 - EISDIR */
  N_("Invalid argument"),		/* 25 - EINVAL */
  N_("Inappropriate file type of format"),	/* 26 - EFTYPE */
  N_("Illegal byte sequence"),		/* 27 - EILSEQ */
  unknown_error,			/* 28 */
  unknown_error,			/* 29 */
  unknown_error,			/* 30 */
  unknown_error,			/* 31 */
  N_("Function not implemented"),	/* 32 - ENOSYS */
  N_("No such file or directory"),	/* 33 - ENOENT */
  N_("Not a directory"),		/* 34 - ENOTDIR */
  N_("Too many open files"),		/* 35 - EMFILE */
  N_("Permission denied"),		/* 36 - EACCES */
  N_("Bad file descriptor"),		/* 37 - EBADF */
  N_("Operation not permitted"),	/* 38 - EPERM */
  N_("Cannot allocate memory"),		/* 39 - ENOMEM */
  N_("Bad address"),			/* 40 - EFAULT */
  unknown_error,			/* 41 */
  unknown_error,			/* 42 */
  unknown_error,			/* 43 */
  unknown_error,			/* 44 */
  unknown_error,			/* 45 */
  N_("No such device or address"),	/* 46 - ENXIO */
  unknown_error,			/* 47 */
  N_("Cross-device link"),		/* 48 - EXDEV */
  N_("No more matching filenames"),	/* 49 - ENMFILES */
  N_("File table overflow"),		/* 50 - ENFILE */ 
  unknown_error,			/* 51 */
  unknown_error,			/* 52 */
  unknown_error,			/* 53 */
  unknown_error,			/* 54 */
  unknown_error,			/* 55 */
  unknown_error,			/* 56 */
  unknown_error,			/* 57 */
  N_("Locking conflict"),		/* 58 - ELOCKED */
  N_("No such lock"),			/* 59 - ENSLOCK */
  unknown_error,			/* 60 */
  unknown_error,			/* 61 */
  unknown_error,			/* 62 */
  unknown_error,			/* 63 */
  N_("Bad argument"),			/* 64 - EBADARG */
  N_("Internal error"),			/* 65 - EINTERNAL */
  N_("Invalid executable file format"),	/* 66 - ENOEXEC */
  N_("Memory block growth failure"),	/* 67 - ESBLOCK */
  N_("Aborted by user"),		/* 68 - EBREAK */
  N_("Terminated with bombs"),		/* 69 - EXCPT */
  N_("Text file busy"),			/* 70 - ETXTBSY */
  N_("File too big"),			/* 71 - EFBIG */
  unknown_error,			/* 72 */
  unknown_error,			/* 73 */
  unknown_error,			/* 74 */
  unknown_error,			/* 75 */
  unknown_error,			/* 76 */
  unknown_error,			/* 77 */
  unknown_error,			/* 78 */
  unknown_error,			/* 79 */
  N_("Too many symbolic links"),	/* 80 - ELOOP */
  N_("Broken pipe"),			/* 81 - EPIPE */
  N_("Too many links"),			/* 82 - EMLINK */
  N_("Directory not empty"),		/* 83 - ENOTEMPTY */
  unknown_error,			/* 84 */
  N_("File exists"),			/* 85 - EEXIST */
  N_("Name too long"),			/* 86 - ENAMETOOLONG */
  N_("Not a tty"),			/* 87 - ENOTTY */
  N_("Range error"),			/* 88 - ERANGE */
  N_("Domain error"),			/* 89 - EDOMAIN */
  N_("I/O error"),			/* 90 - EIO */
  N_("No space on device"),		/* 91 - ENOSPC */
  unknown_error,			/* 92 */
  unknown_error,			/* 93 */
  unknown_error,			/* 94 */
  unknown_error,			/* 95 */
  unknown_error,			/* 96 */
  unknown_error,			/* 97 */
  unknown_error,			/* 98 */
  unknown_error,			/* 99 */
  N_("Too many processes"),		/* 100 - EPROCLIM */
  N_("Too many users"), 		/* 101 - EUSERS */
  N_("Quota exceeded"),			/* 102 - EDQUOT */
  N_("Stale NFS file handle"),		/* 103 - ESTALE */
  N_("Object is remote"),		/* 104 - EREMOTE */
  N_("RPC struct is bad"),		/* 105 - EBADRPC */
  N_("RPC version wrong"),		/* 106 - ERPCMISMATCH */
  N_("RPC program not available"),	/* 107 - EPROGUNAVAIL */
  N_("RPC program version wrong"),	/* 108 - EPROGMISMATCH */
  N_("RPC bad procedure for program"),	/* 109 - EPROCUNAVAIL */
  N_("No locks available"),		/* 110 - ENOLCK */
  N_("Authentication error"),		/* 111 - EAUTH */
  N_("Need authenticator"),		/* 112 - ENEEDAUTH */
  N_("Inappropriate operation for background process"),	/* 113 - EBACKGROUND */
  N_("Not a data message"),		/* 114 - EBADMSG */
  N_("Identifier removed"),		/* 115 - EIDRM */
  N_("Multihop attempted"),		/* 116 - EMULTIHOP */
  N_("No data available"),		/* 117 - ENODATA */
  N_("Link has been severed"),		/* 118 - ENOLINK */
  N_("No message of desired"),		/* 119 - ENOMSG */
  N_("Out of streams resources"),	/* 120 - ENOSR */
  N_("Device not a stream"),		/* 121 - ENOSTR */
  N_("Value too large for defined data type"),	/* 122 - EOVERFLOW */
  N_("Protocol error"),			/* 123 - EPROTO */
  N_("Timer expired"),			/* 124 - ETIME */
  N_("Argument list too long"),		/* 125 - E2BIG */
  N_("Interrupted system call restarted"),	/* 126 - ERESTART */
  N_("Channel number out of range"),	/* 127 - ECHRNG */
  N_("Interrupted function call"),	/* 128 - EINTR */
  N_("Sound system is already locked"), /* 129 - ESNDLOCKED */
  N_("Sound system is not locked"),	/* 130 - ESNDNOTLOCK */
  N_("Level 2 not synchronized"),	/* 131 - EL2NSYNC */
  N_("Level 3 halted"),			/* 132 - EL3HLT */
  N_("Level 3 reset"),			/* 133 - EL3RST */
  N_("Link number out of range"),	/* 134 - ELNRNG */
  N_("Protocol driver not attached"),	/* 135 - EUNATCH */
  N_("No CSI structure available"),	/* 136 - ENOCSI */
  N_("Level 2 halted"),			/* 137 - EL2HLT */
  N_("Invalid exchange"),		/* 138 - EBADE */
  N_("Exchange full"),			/* 139 - EXFULL */
  N_("No anode"),			/* 140 - ENOANO */
  N_("Invalid request code"),		/* 141 - EBADRQC */
  N_("Invalid slot"),			/* 142 - EBADSLT */
  N_("Bad font file format"),		/* 143 - EBFONT */
  N_("Machine is not on the network"),	/* 144 - ENONET */
  N_("Package is not installed"),	/* 145 - ENOPKG */
  N_("Advertise error"),		/* 146 - EADV */
  N_("Srmount error"),			/* 147 - ESRMNT */
  N_("Communication error on send"),	/* 148 - ECOMM */
  N_("RFS specific error"),		/* 149 - EDOTDOT */
  N_("Cannot access a needed shared library"),	/* 150 - ELIBACC */
  N_("Accessing a corrupted shared library"),	/* 151 - ELIBBAD */
  N_(".lib section in a.out corrupted"),	/* 152 - ELIBSCN */
  N_("Attempting to link in too many shared libraries"), /* 153 - ELIBMAX */
  N_("Cannot exec a shared library directly"),	/* 154 - ELIBEXEC */
  N_("Streams pipe error"),		/* 155 - ESTRPIPE */
  N_("Structure needs cleaning"),	/* 156 - EUCLEAN */
  N_("Not a XENIX named type file"),	/* 157 - ENOTNAM */
  N_("No XENIX semaphores available"),	/* 158 - ENAVAIL */
  N_("Remote I/O error"),		/* 159 - EREMOTEIO */
  /* 160 - 299 */
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  unknown_error, unknown_error, unknown_error, unknown_error,
  N_("Socket operation on non-socket"),	/* 300 - ENOTSOCK */
  N_("Destination address required"),	/* 301 - EDESTADDRREQ */
  N_("Message too long"),		/* 302 - EMSGSIZE */
  N_("Protocol wrong type for socket"),	/* 303 - EPROTOTYPE */
  N_("Protocol not available"),		/* 304 - ENOPROTOOPT */
  N_("Protocol not supported"),		/* 305 - EPROTONOSUPPORT */
  N_("Socket type not supported"),	/* 306 - ESOCKTNOSUPPORT */
  N_("Operation not supported"),	/* 307 - EOPTNOTSUPP */
  N_("Protocol family not supported"),	/* 308 - EPFNOSUPPORT */
  N_("Address family not supported by protocol"),	/* 309 - EAFNOSUPPORT */
  N_("Address already in use"),		/* 310 - EADDRINUSE */
  N_("Cannot assign requested address"),	/* 311 - EADDRNOTAVAIL */
  N_("Network is down"),		/* 312 - ENETDOWN */
  N_("Network is unreachable"),		/* 313 - ENETUNREACH */
  N_("Network dropped connection on reset"),	/* 314 - ENETRESET */
  N_("Software caused connection abort"),	/* 315 - ECONNABORTED */
  N_("Connection reset by peer"),	/* 316 - ECONNRESET */
  N_("Socket is already connected"),	/* 317 - EISCONN */
  N_("Socket is not connected"),	/* 318 - ENOTCONN */
  N_("Cannot send after shutdown"),	/* 319 - ESHUTDOWN */
  N_("Connection timed out"),		/* 320 - ETIMEDOUT */
  N_("Connection refused"),		/* 321 - ECONNREFUSED */
  N_("Host is down"),			/* 322 - EHOSTDOWN */
  N_("No route to host"),		/* 323 - EHOSTUNREACH */
  N_("Operation already in progress"),	/* 324 - EALREADY */
  N_("Operation now in progress"),	/* 325 - EINPROGRESS */
  N_("Operation would block"),		/* 326 - EAGAIN */
  N_("No buffer space available"),	/* 327 - ENOBUFS */
  N_("Too many references"),		/* 328 - ETOOMANYREFS */
};

int _sys_nerr = (int) (sizeof (_sys_errlist) / sizeof (_sys_errlist[0]));

/* Map error number to descriptive string.  */

static char* unknown = NULL;
static size_t unknown_size = 1;
static char unknown_error2[] = N_("Unknown error");

char*
strerror (errnum)
     int errnum;
{
  if (errnum >= 0 && errnum < _sys_nerr && _sys_errlist[errnum] != unknown_error)
    return ((char*) _(_sys_errlist[errnum]));
  else
    {
      /* Unknown error.  */
      if (unknown == NULL)
        unknown = malloc (unknown_size);
      if (unknown == NULL)
        {
          strcpy (unknown_error2, _("Unknown error"));
          return unknown_error2;
        }
        
      while (1)
        {
          int stored = snprintf (unknown, unknown_size,
          			 _("Unknown error %u"), errnum);
          char* newbuf;
          
          /* Did that work?  */
          if (stored < unknown_size)
            return unknown;
          newbuf = realloc (unknown, unknown_size * 2);
          if (newbuf == NULL)
            {
              strcpy (unknown_error2, _("Unknown error"));
              return unknown_error2;
            }
          unknown_size *= 2;
          unknown = newbuf;
        }
    }
}

weak_alias (_sys_errlist, sys_errlist)
weak_alias (_sys_nerr, sys_nerr)
