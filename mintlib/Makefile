# mintlib/Makefile -- MiNTLib.
# Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

SHELL = /bin/sh

srcdir = .
top_srcdir = ..
subdir = common

include $(top_srcdir)/configvars

# Make install-libs work.
LIBS = 

GENSYS = AWK=$(AWK) $(srcdir)/gensys

default: all

all-here: syscalls.h

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

TESTS = assert assert-perr atexit ctype ctype1 dirent mallocbug seekdir \
setjmp setjmp1 

include $(top_srcdir)/checkrules

check-local: 

install-include:

install-man:

uninstall-include:

uninstall-man:

distdir:

bindistdir:

syscalls.h: $(srcdir)/syscalls.list $(srcdir)/gensys
	$(GENSYS) -array $(srcdir)/syscalls.list >$@
