# syscall/Makefile -- MiNTLib.
# Copyright (C) 2001 Frank Naumann <fnaumann@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

SHELL = /bin/sh

srcdir = .
top_srcdir = ..
subdir = syscall

SUBDIRS = 

have_check = no

include $(top_srcdir)/configvars

default: all

gen_objs = check.o generate.o main.o pars.o scan.o traps.o
gen_objs += syscallparser.c

all-here: syscalls.stmp

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

# FIXME: Tests still missing.
TESTS = dummy
include $(top_srcdir)/checkrules

# Override test flags.
cflags = -O -Wall
type = 

syscalls.stmp: gen-syscall0 syscalls.master
	echo "TRAPS=" > SRCFILES.traps
	./gen-syscall syscalls.master
	touch $@

gen-syscall0:
	$(MAKE) gen-syscall CC="$(CC_FOR_BUILD)" CFLAGS="-O -Wall" COMPILE="$(CC_FOR_BUILD) -O -Wall"

gen-syscall: $(gen_objs)
	$(CC) $(gen_objs) -o $@ -lfl

%.c: %.y
	bison -d --output=$@ $<

%.c: %.l
	flex -o$@ $<

install: all-here

uninstall:

install-man:

uninstall-man:

