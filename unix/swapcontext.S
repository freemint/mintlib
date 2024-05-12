/* Save current context and install the given one.
   Copyright (C) 2012-2022 Free Software Foundation, Inc.
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

ENTRY(__swapcontext)
	cfi_startproc
#ifndef __FASTCALL__
	/* Load address of the context data structure we save in.  */
	move.l	4(%sp), %a0
	/* Load address of the context data structure we have to load.  */
	move.l	8(%sp), %a1
#endif

	/* Save the preserved registers and the return address.  */
	movem.l	%d2-%d7, oGREGS+2*4(%a0)
	movem.l	%a2-%a6, oGREGS+10*4(%a0)
	move.l	%sp, %d0
	addq.l	#4,%d0
	move.l	%d0, oSP(%a0)
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
	cfi_offset (%a2, oGREGS+10*4)
	cfi_offset (%pc, oPC)

	/* Save the current signal mask and install the new one.  */
	move.l	oSIGMASK(%a1), %d0
	movel	%d0, C_SYMBOL_NAME(_sigmask)		/* restore tos emulation signal mask */
	movel	%a1, %sp@-		/* save register a0 */
	movel	%d0, %sp@-		/* restore signal mask */
	movew	#0x117, %sp@-		/* Psigsetmask() system call */
	trap	#1
	addql	#6, %sp
	movel	%sp@+, %a1		/* restore register a1 */
	move.l	%d0,oSIGMASK(%a1)

	/* Load the new stack pointer.  */
	move.l	oSP(%a1), %sp
	cfi_def_cfa (%a1, 0)
	cfi_offset (%d2, oGREGS+2*4)
	cfi_offset (%d3, oGREGS+3*4)
	cfi_offset (%d4, oGREGS+4*4)
	cfi_offset (%d5, oGREGS+5*4)
	cfi_offset (%d6, oGREGS+6*4)
	cfi_offset (%d7, oGREGS+7*4)
	cfi_offset (%a2, oGREGS+10*4)
	cfi_offset (%a3, oGREGS+11*4)
	cfi_offset (%a4, oGREGS+12*4)
	cfi_offset (%a5, oGREGS+13*4)
	cfi_offset (%a6, oGREGS+14*4)
#ifdef __mcoldfire__
	cfi_offset (%fp2, oFP2+0*8)
	cfi_offset (%fp3, oFP2+1*8)
	cfi_offset (%fp4, oFP2+2*8)
	cfi_offset (%fp5, oFP2+3*8)
	cfi_offset (%fp6, oFP2+4*8)
	cfi_offset (%fp7, oFP2+5*8)
#else
	cfi_offset (%fp2, oFP2+0*12)
	cfi_offset (%fp3, oFP2+1*12)
	cfi_offset (%fp4, oFP2+2*12)
	cfi_offset (%fp5, oFP2+3*12)
	cfi_offset (%fp6, oFP2+4*12)
	cfi_offset (%fp7, oFP2+5*12)
#endif
	cfi_offset (%pc, oPC)

	/* Load the values of all the preserved registers (except SP).  */
	movem.l	oGREGS+2*4(%a1), %d2-%d7
	movem.l	oGREGS+10*4(%a1), %a2-%a6
#ifdef __mcoldfire__
	fmove.l oFPREGS(%a1), %fpcr
	fmove.l oFPREGS+4(%a1), %fpsr
	fmove.l oFPREGS+8(%a1), %fpiar
	fmovem.d oFP2(%a1), %fp2-%fp7
#else
#ifdef __HAVE_68881__
	fmovem.l oFPREGS(%a1), %fpsr/%fpcr/%fpiar
	fmovem.x oFP2(%a1), %fp2-%fp7
#endif
#endif

	/* Clear D0 to indicate success.  */
	clr.l	%d0

	/* Fetch the address to return to.  */
	move.l	oPC(%a1), %a0

	/* End FDE here, we fall into another context.  */
	cfi_endproc
	cfi_startproc
	cfi_register (%pc, %a0)

	jmp	(%a0)

	cfi_offset (%pc, -4)
PSEUDO_END(__swapcontext)
	cfi_endproc

weak_alias (__swapcontext, swapcontext)

#include "elfattr.S"
