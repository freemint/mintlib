# syscall/Makefile -- MiNTLib.
# Copyright (C) 2001 Frank Naumann <fnaumann@freemint.de>
# $Id$
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

gen_objs = check.o generate.o list.o main.o pars.o scan.o traps.o

all-here: syscalls.stmp

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

# FIXME: Tests still missing.
TESTS = dummy
include $(top_srcdir)/checkrules

# Override test flags.
cflags = -O -Wall
type = 

# override (cross)compiler
CC = gcc
CFLAGS = -Wall -O
COMPILE = $(CC) $(CFLAGS)

syscalls.stmp: gen-syscall syscalls.master
	./gen-syscall syscalls.master
	touch $@

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

