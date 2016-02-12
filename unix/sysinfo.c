/*  sysinfo.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/systeminfo.h>
#include <sys/utsname.h>
#include <sys/param.h>
#include <mint/cookie.h>
#include <mint/mintbind.h>

#include "lib.h"


/* Helper functions.  */
static void fast_strncpy (char* to, char* from, long bytes);

/* Prototypes for sub-functions.  */

/* Standard (more or less).  */
static int si_sysname (char *buf, long bufsize);
static int si_hostname (char *buf, long bufsize);
static int si_set_hostname (char *buf, long bufsize);
static int si_release (char *buf, long bufsize);
static int si_version (char *buf, long bufsize);
static int si_architecture (char *buf, long bufsize);
static int si_isalist (char *buf, long bufsize);
static int si_platform (char *buf, long bufsize);
static int si_hw_provider (char *buf, long bufsize);

/* Interface to Ssystem.  */
static int mint_kernel_build_date (char *buf, long bufsize);
static int mint_kernel_build_time (char *buf, long bufsize);
static int mint_get_clock_mode (char *buf, long bufsize);
static int mint_set_clock_mode (char *buf, long bufsize);

int
__sysinfo (enum __sysinfo_command command, char *buf, long bufsize)
{
  int retval = -1;

  /* Pathological cases first.  */
  if (buf == NULL && bufsize > 0) {
    __set_errno (EFAULT);
    return -1;
  }

  switch (command) {
    case SI_SYSNAME:
      retval = si_sysname (buf, bufsize);
      break;
    case SI_HOSTNAME:
      retval = si_hostname (buf, bufsize);
      break;
    case SI_SET_HOSTNAME:
      retval = si_set_hostname (buf, bufsize);
      break;
    case SI_RELEASE:
      retval = si_release (buf, bufsize);
      break;
    case SI_VERSION:
      retval = si_version (buf, bufsize);
      break;
    case SI_ARCHITECTURE:
      retval = si_architecture (buf, bufsize);
      break;
    case SI_ISALIST:
      retval = si_isalist (buf, bufsize);
      break;
    case SI_PLATFORM:
      retval = si_platform (buf, bufsize);
      break;
    case SI_HW_PROVIDER:
      retval = si_hw_provider (buf, bufsize);
      break;
    case _MINT_SI_KERNEL_BUILD_DATE:
      retval = mint_kernel_build_date (buf, bufsize);
      break;
    case _MINT_SI_KERNEL_BUILD_TIME:
      retval = mint_kernel_build_time (buf, bufsize);
      break;
    case _MINT_SI_GET_CLOCK_MODE:
      retval = mint_get_clock_mode (buf, bufsize);
      break;
    case _MINT_SI_SET_CLOCK_MODE:
      retval = mint_set_clock_mode (buf, bufsize);
      break;
    default:
      __set_errno (EINVAL);
      retval = -1;
  }
  return retval;
}
weak_alias (__sysinfo, sysinfo)

/* Like strncpy but don't pad with nulls.  */
static void
fast_strncpy (to, from, bytes)
  char* to;
  char* from;
  long bytes;
{
  long count = 0;

  if (bytes <= 0)
    return;

  while (*from && ++count < bytes)
    *to++ = *from++;
  *to = '\0';
}

/*
 * SI_SYSNAME
 * FIXME: Should we look up information about MagiC too?
 */

static char* osname = NULL;  /* Cached result.  */
static int osname_len = 0;   /* Cached result.  */

static char* osnames[] = {
#define OS_TOS 0
  "TOS",
#define OS_MINT 1
  "MiNT",
#define OS_FREEMINT 2
  "FreeMiNT"
};

static int
si_sysname (buf, bufsize)
  char* buf;
  long bufsize;
{
  if (osname == NULL) {
    int index = OS_TOS;
    /* This is non-standard.  But it may be helpful.  */
    osname = getenv ("SYSTEMNAME");

    if (osname == NULL) {
      if (__mint > 0x0000010cL)
        index = OS_FREEMINT;
      else if (__mint > 0)
        index = OS_MINT;
      osname = osnames[index];
    }
    osname_len = strlen (osname) + 1;
  }

  fast_strncpy (buf, osname, bufsize);
  return osname_len;
}

/*
 * SI_HOSTNAME
 * For the moment we simply look up /etc/hostname.  Of course
 * the result of the lookup is not cached.
 */
static int
si_hostname (buf, bufsize)
  char* buf;
  long bufsize;
{
  int saved_errno = errno;

  __set_errno (0);

  if (gethostname (buf, bufsize) != 0) {
    if (errno == ENAMETOOLONG) {
      __set_errno (saved_errno);
      return MAXHOSTNAMELEN;
    }
    return -1;
  }

  __set_errno (saved_errno);
  return (strlen (buf) + 1);
}

/*
 * SI_SET_HOSTNAME
 * Calls the stubs function sethostname().
 */
static int
si_set_hostname (buf, bufsize)
  char* buf;
  long bufsize;
{
  return (sethostname (buf, bufsize));
}

/* SI_RELEASE
 * This is either the MiNT or the GEMDOS version number.
 */

static int
si_release (buf, bufsize)
  char* buf;
  long bufsize;
{
  /* Cached results.  */
  static char* osrelease = NULL;
  static char osrelease_buf[13];
  static long osrelease_len;
  static long mintversion;

  if (osrelease == NULL) {
    unsigned long main_rev = 0;
    unsigned long sub_rev = 0;
    unsigned long patch_level = 0;
    char betatag[2] = "";
    int gotcha = 0;
    long ver = Ssystem (2, 0, 0);

    if (ver == -ENOSYS) {
      /* This is actually a bug in Ssystem () because the return code
       * of -32 would also describe version 255.255.255<greak alpha>.
       */
      /* Fall thru'.  */
    } else if (ver < 0) {
      __set_errno (-ver);
      return -1;
    } else {
      main_rev = (ver & 0xff000000) >> 24;
      sub_rev = (ver & 0xff0000) >> 16;
      patch_level = (ver & 0xff00) >> 8;
      if (ver & 0xff) {
        betatag[0] = ver & 0xff;
        betatag[1] = '\0';
      }
      gotcha = 1;
    }

    if (!gotcha && __mint) {
      main_rev = (__mint & 0xff00) >> 8;
      sub_rev = __mint & 0xff;
    } else if (!gotcha) {
      unsigned long ver = Sversion ();

      /* OK, this is actually bogus for GEMDOS because SUB_REV is
       * really the main revision and PATCH_LEVEL is really the
       * sub revision but it works and the user won't see our
       * variable names.
       */
      sub_rev = ((ver & 0xf000) >> 12) * 10 + ((ver & 0xf00) >> 8);
      patch_level = ((ver & 0xf0) >> 4) * 10 + (ver & 0xf);
    }
    if (patch_level)
      sprintf (osrelease_buf, "%lu.%lu.%lu%s", main_rev, sub_rev, patch_level, betatag);
    else
      sprintf (osrelease_buf, "%lu.%lu%s", main_rev, sub_rev, betatag);
    osrelease = osrelease_buf;
    osrelease_len = strlen (osrelease) + 1;
    mintversion = (main_rev << 24) | (sub_rev << 16)
        | (patch_level << 8) | betatag[0];
  }

  fast_strncpy (buf, osrelease, bufsize);
  return osrelease_len;
}

/* SI_VERSION
 * BUGS: This is always the TOS version number.  Be it non-standard
 *       or not, this is the way the uname() function in the MiNTLibs
 *       handled stuff.  We'll stick to that behavior because it
 *       has proofed to be practicable.
 */

static int
si_version (buf, bufsize)
  char* buf;
  long bufsize;
{
  /* Cached results.  */
  static char* osversion = NULL;
  static char osversion_buf[22];
  static long osversion_len;
  static long tosversion;


	if (osversion == NULL)
	{
		void* save_stk;
		long* sysbase;
		char hi, lo;

		if (Ssystem(-1, NULL, NULL))
		{
			if (Super(1L) == 0L)
			{
				save_stk = (void *) Super (0L);
				sysbase = *((long int**) 0x000004f2);
				tosversion = *sysbase;
				(void) SuperToUser ((void*) save_stk);
			}
			else
			{
				sysbase = *((long int**) 0x000004f2);
				tosversion = *sysbase;
			}
		}
		else
		{
			tosversion = Ssystem(3, 0, NULL);
		}

		hi = (tosversion & 0xff00) >> 8;
		lo = (tosversion & 0xff);

		sprintf (osversion_buf, "%d.%d", (int) hi, (int) lo);
		osversion = osversion_buf;
		osversion_len = strlen (osversion) + 1;
	}

	fast_strncpy (buf, osversion, bufsize);

	return osversion_len;
}

/* SI_ARCHITECTURE */

/* Cached results.  */

static char* architecture = NULL;
static long architecture_len;
#define _CPU_60 0
#define _CPU_40 1
#define _CPU_30 2
#define _CPU_20 3
#define _CPU_10 4
#define _CPU_00 5
#define _MCF_V5 6
#define _MCF_V4 7
#define _MCF_V3 8
#define _MCF_V2 9
#define _MCF_V1 10

static char* architectures[] = {
  "mc68060",
  "mc68040",
  "mc68030",
  "mc68020",
  "mc68010",
  "mc68000",
  "cfv5",
  "cfv4",
  "cfv3",
  "cfv2",
  "cfv1",
  NULL
};

static char* isalist = NULL;
long isalist_len;
#define _ISA_C        6
#define _ISA_B        7
#define _ISA_A_PLUS   8
#define _ISA_A        9

static char* isalists[] = {
    "mc68060", "mc68040", "mc68030", "mc68020", "mc68010", "mc68000",
     "isac", "isab", "isaaplus", "isaa"};

static int
si_architecture (buf, bufsize)
  char* buf;
  long bufsize;
{
  if (architecture == NULL) {
    long int value = 0;
    int cpu = _CPU_00;
    MCF_COOKIE *mcf_cookie;

    /* m68k */
    if (!Getcookie (C__CPU, &value)) {
      if (value >= 60)
        cpu = _CPU_60;
      else if (value >= 40)
        cpu = _CPU_40;
      else if (value >= 30)
        cpu = _CPU_30;
      else if (value >= 20)
        cpu = _CPU_20;
      else if (value >= 10)
        cpu = _CPU_10;
      architecture_len = sizeof ("mc68xxx");
      isalist = isalists[cpu];
    }
    /* ColdFire */
    else if (!Getcookie (C__MCF, &value)) {
      mcf_cookie = (MCF_COOKIE *)value;

      if (mcf_cookie->magic[0] == 'M' &&
          mcf_cookie->magic[1] == 'C' &&
          mcf_cookie->magic[2] == 'F' &&
          mcf_cookie->version ==   1)
      {
        switch (mcf_cookie->core) {
          case 1:
            cpu = _MCF_V1;
            break;
          case 2:
            cpu = _MCF_V2;
            break;
          case 3:
            cpu = _MCF_V3;
            break;
          case 4:
            cpu = _MCF_V4;
            break;
          case 5:
            cpu = _MCF_V5;
            break;
        }
        switch (mcf_cookie->isa) {
          case MCF_ISA_A:
            isalist = isalists[_ISA_A];
            break;
          case MCF_ISA_B:
            isalist = isalists[_ISA_B];
            break;
          case MCF_ISA_C:
            isalist = isalists[_ISA_C];
            break;
          case MCF_ISA_A_PLUS:
            isalist = isalists[_ISA_A_PLUS];
            break;
         }
        architecture_len = sizeof ("cfvx");
      }
    }

    architecture = architectures[cpu];
    isalist_len = strlen (isalist) + 1;
  }

  fast_strncpy (buf, architecture, bufsize);
  return architecture_len;
}

/* SI_ISALIST */
static int
si_isalist (buf, bufsize)
  char* buf;
  long bufsize;
{
  if (isalist == NULL)
    (void) si_architecture (NULL, 0);

  fast_strncpy (buf, isalist, bufsize);
  return isalist_len;
}

/* SI_PLATFORM
 * BUGS: The value for the falcon is just a guess.  What about
 *       distinct values for the _MCH cookie for clones?
 */

#define _PLATFORM_ST 0
#define _PLATFORM_STE 1
#define _PLATFORM_TT 2
#define _PLATFORM_FALCON 3
#define _PLATFORM_MILAN 4
#define _PLATFORM_HADES 5
#define _PLATFORM_ARANYM 6
#define _PLATFORM_FIREBEE 7
#define _PLATFORM_CFEVB 8
#define _PLATFORM_CLONE 9

static char* platforms[] = {
  "atarist",
  "atariste",
  "ataritt",
  "falcon",
  "milan",
  "hades",
  "aranym",
  "firebee",
  "cfevb"
  "atariclone",
};

#define _HW_PROVIDER_ATARI 0
#define _HW_PROVIDER_MILAN 1
#define _HW_PROVIDER_HADES 2
#define _HW_PROVIDER_ARANYM 3
#define _HW_PROVIDER_FREESCALE 4
#define _HW_PROVIDER_UNKNOWN 5
static char* hw_providers[] = {
  "atari",
  "milan",
  "hades",  /* This should have been "medusa" */
  "aranym",
  "freescale",
  "unknown"
};

/* Cached results.  */
static char* platform = NULL;
static char* hw_provider = NULL;
static long platform_len;
static long hw_provider_len;

static int
si_platform (buf, bufsize)
  char* buf;
  long bufsize;
{
  if (platform == NULL) {
    long _mch = 0;  /* = AtariST */
    short hi, lo;
    int coldfire = 0;
    long dummy;

    /* If we find the Hades cookie ignore the rest.  */
    if (Getcookie (C_hade, &_mch) == 0) {
      platform = platforms[_PLATFORM_HADES];
      hw_provider = hw_providers[_HW_PROVIDER_HADES];
    } else {
      /* Check for ColdFire CPU */
      if (!Getcookie (C__CF_, &dummy))
        coldfire = 1;

      (void) Getcookie (C__MCH, &_mch);
      hi = (_mch & 0xffff0000) >> 16;
      lo = (_mch & 0xffff);

      switch (hi) {
        case -1:
          if(coldfire) {
            platform = platforms[_PLATFORM_CFEVB];
            hw_provider = hw_providers[_HW_PROVIDER_FREESCALE];
          }
          break;
        case 0:
          platform = platforms[_PLATFORM_ST];
          hw_provider = hw_providers[_HW_PROVIDER_ATARI];
          break;
        case 1:
          platform = platforms[_PLATFORM_STE];
          hw_provider = hw_providers[_HW_PROVIDER_ATARI];
          break;
        case 2:
          platform = platforms[_PLATFORM_TT];
          hw_provider = hw_providers[_HW_PROVIDER_ATARI];
          break;
        case 3:
          if(coldfire) {
            platform = platforms[_PLATFORM_FIREBEE];
            hw_provider = hw_providers[_HW_PROVIDER_HADES];
          } else {
            platform = platforms[_PLATFORM_FALCON];
            hw_provider = hw_providers[_HW_PROVIDER_ATARI];
          }
          break;
        case 4:
          platform = platforms[_PLATFORM_MILAN];
          hw_provider = hw_providers[_HW_PROVIDER_MILAN];
          break;
        case 5:
          platform = platforms[_PLATFORM_ARANYM];
          hw_provider = hw_providers[_HW_PROVIDER_ARANYM];
          break;
        default:
          platform = platforms[_PLATFORM_CLONE];
          hw_provider = hw_providers[_HW_PROVIDER_UNKNOWN];
          break;
      }
    }

    platform_len = strlen (platform) + 1;
    hw_provider_len = strlen (hw_provider) + 1;
  }

  fast_strncpy (buf, platform, bufsize);
  return platform_len;
}

/* SI_HW_PROVIDER */
static int
si_hw_provider (buf, bufsize)
  char* buf;
  long bufsize;
{
  if (platform == NULL)
    (void) si_platform (NULL, 0);

  fast_strncpy (buf, hw_provider, bufsize);
  return hw_provider_len;
}

/* Cached results.  */
static int no_build_date = 0;
static char* kernel_build_date = NULL;
static char kernel_build_date_buf[] = "Mmm DD YYYY";
#define kernel_build_date_len ((long) sizeof kernel_build_date_buf)

static char* abbrev_month_names[] = {
  "Jan",
  "Feb",
  "Mar",
  "Apr",
  "May",
  "Jun",
  "Jul",
  "Aug",
  "Sep",
  "Oct",
  "Nov",
  "Dec"
};

/* _MINT_SI_KERNEL_BUILD_DATE */
static int
mint_kernel_build_date (buf, bufsize)
  char* buf;
  long bufsize;
{
  char* rbuf;

  if (no_build_date) {
    __set_errno (ENOSYS);
    return -1;
  }

  if (kernel_build_date == NULL) {
    long retval = Ssystem (4, 0, 0);
    if (retval == -ENOSYS) {
      __set_errno (ENOSYS);
      no_build_date = 1;
      return -1;
    } else if (retval < 0) {
      __set_errno (EINVAL);
      return -1;
    } else {
      unsigned char day, mon;
      unsigned short* year;
      rbuf = (char*) &retval;

      kernel_build_date = kernel_build_date_buf;
      day = (unsigned char) rbuf[0];
      mon = (unsigned char) rbuf[1];
      year = (unsigned short*) &rbuf[2];

      /* Bug in 1.14.7.  */
      if (mon < 1)
        mon = 1;
      else if (mon > 12)
        mon = 12;
      sprintf (kernel_build_date, "%.02u %s %.04u",
          (unsigned) day,
          abbrev_month_names[mon - 1],
          (unsigned) *year);
    }
  }

  fast_strncpy (buf, kernel_build_date, bufsize);
  return kernel_build_date_len;
}

/* _MINT_SI_KERNEL_BUILD_TIME */

/* Cached results.  */
static int no_build_time = 0;
static char* kernel_build_time = NULL;
static char kernel_build_time_buf[] = "HH:MM:SS";
#define kernel_build_time_len ((long) sizeof kernel_build_time_buf)

static int
mint_kernel_build_time (buf, bufsize)
  char* buf;
  long bufsize;
{
  if (no_build_time) {
    __set_errno (ENOSYS);
    return -1;
  }

  if (kernel_build_time == NULL) {
    long retval = Ssystem (5, 0, 0);
    if (retval == -ENOSYS) {
      __set_errno (ENOSYS);
      no_build_time = 1;
      return -1;
    } else if (retval < 0) {
      __set_errno (EINVAL);
      return -1;
    } else {
      char* rbuf = (char*) &retval;
      kernel_build_time = kernel_build_time_buf;
      sprintf (kernel_build_time, "%.02u:%.02u:%.02u",
          (unsigned) rbuf[1], (unsigned) rbuf[2], (unsigned) rbuf[3]);
    }
  }

  fast_strncpy (buf, kernel_build_time, bufsize);
  return kernel_build_time_len;
}

#include <stdio.h>
static int
mint_get_clock_mode (buf, bufsize)
  char* buf;
  long bufsize;
{
  char* clock_mode = NULL;
  long int lclock_mode;

  lclock_mode = Ssystem (100, -1, 0);
  if (lclock_mode == -ENOSYS) {
    __set_errno (ENOSYS);
    no_build_time = 1;
    return -1;
  } else if (lclock_mode < 0) {
    __set_errno (EINVAL);
    return -1;
  } else {
    if (lclock_mode == 0)
      clock_mode = "UTC";
    else
      clock_mode = "local";
  }

  fast_strncpy (buf, clock_mode, bufsize);
  return strlen (clock_mode);
}

static int
mint_set_clock_mode (buf, bufsize)
  char* buf;
  long bufsize;
{
  long int lclock_mode = 1;
  long int retval;

  (void) bufsize;

  if (buf == NULL) {
    __set_errno (EFAULT);
    return -1;
  }

  if (strncmp (buf, "UTC", 3) == 0 || strncmp (buf, "GMT", 3) == 0)
    lclock_mode = 0;

  retval = Ssystem (100, lclock_mode, 0);
  if (retval == -ENOSYS) {
    __set_errno (ENOSYS);
    return -1;
  } else if (retval < 0) {
    __set_errno (-retval);
    return -1;
  }

  return 0;
}
