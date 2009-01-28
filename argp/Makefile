# string/Makefile -- MiNTLib.
# Copyright (C) 2000 Guido Flohr <guido@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

SHELL = /bin/sh

srcdir = .
top_srcdir = ..
subdir = argp 

SUBDIRS =

have_check = yes

include $(top_srcdir)/configvars

# Make install-libs work.
LIBS = 

default: all

all-here:

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

# FIXME: stratcliff still missing because of missing mman.h.
TESTS = argp1 argp2 bug-argp1 argp
EXTRAPRGS =
CFLAGS-test-argp1.c = -fno-builtin
CFLAGS-test-argp2.c = -fno-builtin
CFLAGS-test-bug-argp1.c = -fno-builtin
CFLAGS-test-argp.c = -fno-builtin
# If you don't optimize you cannot test the inline versions.
EXTRACFLAGS = -O
include $(top_srcdir)/checkrules

check-local:

install-include:

uninstall-include:

install-man:

uninstall-man:
