| setstack.S -- MiNTLib.
| Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>
|
| This file is part of the MiNTLib project, and may only be used
| modified and distributed under the terms of the MiNTLib project
| license, COPYMINT.  By continuing to use, modify, or distribute
| this file you indicate that you have read the license and
| understand and accept it fully.
|

|
| _setstack: changes the stack pointer; called as
|     void setstack( void *newsp )
| called from crtinit.c once the new stack size has been decided upon
|
| WARNING WARNING WARNING: after you do this, local variables may no longer
| be accessible!
| destroys a0 and a7

	.globl	__setstack
__setstack:
	movel	sp@+, a0	| save return address
	movel	sp@, sp		| new stack pointer
	subql	#4, sp		| fixup for tidy upon return
	jmp	a0@		| back to caller

