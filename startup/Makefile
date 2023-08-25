# startup/Makefile -- MiNTLib.
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
subdir = startup

default: all

dont_install_libs = yes

include $(top_srcdir)/configvars
include $(top_srcdir)/bindist

libdir = $(prefix)/lib

INCLUDES = -nostdinc -I$(top_srcdir)/include -I$(top_srcdir)/mintlib

COMPILE = $(CC) $(WARN) $(CFLAGS) $(INCLUDES) $(DEFS)

all-here:

include $(top_srcdir)/phony

include $(top_srcdir)/rules

install: all-here

uninstall:
	
install-include:

install-man:

uninstall-include:

uninstall-man:

checkclean:

