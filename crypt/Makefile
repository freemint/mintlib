# crypt/Makefile -- MiNTLib.
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
subdir = crypt

SUBDIRS = examples

have_check = yes

default: all

include $(top_srcdir)/configvars

# Make install-libs work.
LIBS = 

default: all

all-here:

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

TESTS = cert md5_1 md5_2 ufc
EXTRAPRGS = speeds md5speeds
CFLAGS-speeds.c = -O3 -fomit-frame-pointer
CFLAGS-md5speeds.c = -O3 -fomit-frame-pointer
# This is necessary in order to get md5.h to include <limits.h> to find
# the correct size of md5_uint32_t.
DEFS-test-md5_1.c = -D_LIBC -U_GNU_SOURCE -I$(top_srcdir)/mintlib
DEFS-test-md5_2.c = -D_LIBC -U_GNU_SOURCE -I$(top_srcdir)/mintlib

include $(top_srcdir)/checkrules

check-local: $(EXTRAPRGS)
	@echo "====================================================="
	@echo "=== Benchmarking libc crypt (DES and MD5 version) ==="
	@echo "====================================================="
	./speeds
	./md5speeds
	
install-include:

uninstall-include:

install-man:

uninstall-man:

