# stdiio/Makefile -- MiNTLib.
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
subdir = stdiio

SUBDIRS =

default: all

include $(top_srcdir)/configvars

# Make install-libs work.
LIBS = 

default: all

TESTS = iioformat iioscanf iiowc-printf

libs-test-iioformat = $(top_srcdir)/lib$(type)/libiio.a
libs-test-iioscanf = $(top_srcdir)/lib$(type)/libiio.a

include $(top_srcdir)/checkrules

all-here:

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

install-include:

uninstall-include:

install-man:

uninstall-man:
