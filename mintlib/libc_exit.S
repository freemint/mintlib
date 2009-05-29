| libc_exit.S -- MiNTLib.
| Copyright (C) 2000 Guido Flohr <guido@freemint.de>
|
| This file is part of the MiNTLib project, and may only be used
| modified and distributed under the terms of the MiNTLib project
| license, COPYMINT.  By continuing to use, modify, or distribute
| this file you indicate that you have read the license and
| understand and accept it fully.

| This file is in assembler to avoid it being profiled when compiling
| with -pg.

#include <libc-symbols.h>
	.text
	.even
	.globl ___libc_exit, __exit
	weak_alias (__libc_exit, _exit)
	
___libc_exit:
	link a6,#0
#ifdef __mcoldfire__
	lea	sp@(-12),sp
	moveml	d5/a4/a5,sp@
#else
	moveml	d5/a4/a5,sp@-
#endif
#ifndef __MSHORT__
	movel a6@(8),d3
#else
	movew a6@(8),d3
#endif
| now on _mcleanup handled
|	clrl sp@-
|	jbsr __moncontrol
	
	jbsr ___mcleanup
	movw	d3,sp@-
	movw    #76,sp@-
	trap    #1
