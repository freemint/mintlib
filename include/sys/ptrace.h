/*  sys/ptrace.h -- MiNTLib.
    Copyright (C) 2000 Frank Naumann <fnaumann@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef	_SYS_PTRACE_H
# define _SYS_PTRACE_H	1

#ifndef _FEATURES_H
# include <features.h>
#endif

#ifndef _SYS_TYPES_H
# include <sys/types.h>
#endif

#include <mint/ptrace.h>

__BEGIN_DECLS

#define PTRACE_TRACEME		PT_TRACE_ME
#define PTRACE_PEEKTEXT		PT_READ_I
#define PTRACE_PEEKDATA		PT_READ_D
#define PTRACE_POKETEXT		PT_WRITE_I
#define PTRACE_POKEDATA		PT_WRITE_D
#define PTRACE_CONT		PT_CONTINUE
#define PTRACE_KILL		PT_KILL
#define PTRACE_SINGLESTEP	PT_STEP
#define PTRACE_GETREGS		PT_GETREGS
#define PTRACE_SETREGS		PT_SETREGS
#define PTRACE_GETFPREGS	PT_GETFPREGS
#define PTRACE_SETFPREGS	PT_SETFPREGS
#define PTRACE_ATTACH		PT_ATTACH
#define PTRACE_DETACH		PT_DETACH
#define PTRACE_SYSCALL		PT_SYSCALL

extern int ptrace (int _request, pid_t _pid, caddr_t _addr, int _data) __THROW;

__END_DECLS

#endif	/* ptrace.h  */
