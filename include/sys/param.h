#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H 1

#define	MAXPATHLEN	128		/* same as FILENAME_MAX in stdio.h */
#define	NOFILE		20		/* same as OPEN_MAX in limits.h */

/* Only define MAXHOSTNAMELEN if portlib.h got not included!  I wish
   the portlib was as kind as we are.  */
#ifndef MAXHOSTNAMELEN
# define MAXHOSTNAMELEN 64
#endif

#ifdef __MINT__
# define HZ		200		/* ticks/second reported by times() */
# define NCARGS		1024		/* actually, we don't limit this */
#else
# define HZ		60		/* ticks/second reported by times() */
# define NCARGS		126		/* max. no. of characters in argv */
#endif

#define FSCALE 2048

/* FIXME:  Shouldn't this be 512?  */
#define DEV_BSIZE		1024

/* GNU autoconf checks for BYTE_ORDER here.  We do it the favor.  */
#include <endian.h>

#endif /* _SYS_PARAM_H */
