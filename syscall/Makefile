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

# override crosscompiler
ifdef CROSS
CC = gcc
CFLAGS = -Wall -O
COMPILE = $(CC) $(CFLAGS)
endif

MANS =  
DOCS = 

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
	sections=""; \
	for manpage in $(MANS); do \
	  sections="$$sections $(mandir)/man`echo $$manpage | sed 's,^.*\\.,,'`"; \
	done; \
	mandirs=`echo $$sections | sort | uniq`; \
	for mandir in $$mandirs; do \
	  $(mkinstalldirs) $$mandir; \
	done; \
	for manpage in $(MANS); do \
	  section=`echo $$manpage | sed 's,^.*\\.,,'`; \
	  $(INSTALL) -m 644 $$manpage $(mandir)/man$$section; \
	  echo "$(INSTALL) -m 644 $$manpage $(mandir)/man$$section"; \
	done; \

uninstall-man:
	@for manpage in $(MANS); do \
	  section=`echo $$manpage | sed 's,^.*\\.,,'`; \
	  echo "rm -f $(mandir)/man$$section/$$manpage"; \
	  echo "rm -f $(mandir)/man$$section/$$manpage.gz"; \
	  echo "rm -f $(mandir)/man$$section/$$manpage.Z"; \
	  rm -f $(mandir)/man$$section/$$manpage; \
	  rm -f $(mandir)/man$$section/$$manpage.gz; \
	  rm -f $(mandir)/man$$section/$$manpage.Z; \
	done
