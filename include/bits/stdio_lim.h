/*  bits/stdio_lim.h -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifdef	_STDIO_H

#define L_tmpnam 128

# define TMP_MAX 2147483647

#ifdef __USE_POSIX
# define L_ctermid 128
# define L_cuserid 80
#endif
#define FILENAME_MAX (128)
#undef __need_FOPEN_MAX
#define __need_FOPEN_MAX 1
#endif

#if defined __need_FOPEN_MAX && !defined __defined_FOPEN_MAX
#define FOPEN_MAX 256
#endif
#undef __need_FOPEN_MAX
