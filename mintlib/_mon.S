| _mon.S -- MiNTLib.
| Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>
|
| This file is part of the MiNTLib project, and may only be used
| modified and distributed under the terms of the MiNTLib project
| license, COPYMINT.  By continuing to use, modify, or distribute
| this file you indicate that you have read the license and
| understand and accept it fully.
|

| Dummy interfaces for gprof if not linked against (g)crt0.o.

#ifndef PROFILING

#include "libc-symbols.h"

	.globl 	C_SYMBOL_NAME(_monstartup)
	.globl	C_SYMBOL_NAME(_moncontrol)
	.globl 	C_SYMBOL_NAME(__mcleanup)

C_SYMBOL_NAME(_monstartup):
C_SYMBOL_NAME(_moncontrol):
C_SYMBOL_NAME(__mcleanup):
	rts
#endif
