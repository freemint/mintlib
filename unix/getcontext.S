/* Save current context.
   Copyright (C) 2012-2023 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Modified for MiNTLib by Thorsten Otto.  */

#include "libc-symbols.h"

#include "ucontext_i.h"


ENTRY(__getcontext)
	cfi_startproc
	/* Load address of the context data structure.  */
	move.l	4(%sp), %a0

	/* Save the preserved registers and the return address.  */
	movem.l	%d2-%d7, oGREGS+2*4(%a0)
	movem.l	%a2-%a6, oGREGS+10*4(%a0)
	lea	4(%sp), %a1
	move.l	%a1, oSP(%a0)
	move.l	(%sp), oPC(%a0)
#ifdef __mcoldfire__
	fmove.l %fpcr, oFPREGS(%a0)
	fmove.l %fpsr, oFPREGS+4(%a0)
	fmove.l %fpiar, oFPREGS+8(%a0)
	fmovem.d %fp2-%fp7, oFP2(%a0)
#else
#ifdef __HAVE_68881__
	fmovem.l %fpsr/%fpcr/%fpiar, oFPREGS(%a0)
	fmovem.x %fp2-%fp7, oFP2(%a0)
#endif
#endif
	cfi_def_cfa (%a0, 0)
	cfi_offset (%d2, oGREGS+2*4)
	cfi_offset (%d3, oGREGS+3*4)
	cfi_offset (%pc, oPC)

	/* Save the current signal mask.  */
	movel	%a0, %sp@-		/* save register a0 */
	
	clrl	%sp@-			/* add no signals to sigmask */
	movew	#0x116, %sp@-		/* Psigblock() system call */
	trap	#1
	addql	#6, %sp
	
	movel	%sp@+, %a0		/* restore register a0 */
	tst.l	%d0				/* Check %d0 for error.  */
	jbpl	nomint
	movel	C_SYMBOL_NAME(_sigmask), %d0		/* save tos emulation signal mask */
	
nomint:
#ifdef __mcoldfire__
	orl	#1,%d0			/* make it != 0 (SIGNULL is unmaskable) */
#else
	orw	#1,%d0			/* make it != 0 (SIGNULL is unmaskable) */
#endif
	move.l	%d0, oSIGMASK(%a0)

	/* Restore registers.  */
	cfi_restore (%d2)
	cfi_restore (%d3)
	cfi_def_cfa (%sp, 4)
	cfi_offset (%pc, -4)

	/* All done, return 0 for success.  */
	clr.l	%d0
	rts
PSEUDO_END(__getcontext)
	cfi_endproc

weak_alias (__getcontext, getcontext)
