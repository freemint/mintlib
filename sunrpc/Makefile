# sunrpc/Makefile -- MiNTLib.
# Copyright (C) 2001 Guido Flohr <guido@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

SHELL = /bin/sh

srcdir = .
top_srcdir = ..
subdir = sunrpc

SUBDIRS =

have_check = no

include $(top_srcdir)/configvars

default: all

all-here: rpcgen rpcinfo

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

# FIXME: Tests still missing.
TESTS = dummy
include $(top_srcdir)/checkrules

# Override test flags.
cflags = -O -Wall
type = 

RPCGENOBJS = $(RPCGEN_SRCFILES:.c=.o)
RPCINFOOBJS = $(RPCINFO_SRCFILES:.c=.o)

MANS = bindresvport.3 getrpcport.3 rpc.3 rpc.5 rpcgen.1 rpcinfo.8 xdr.3 
DOCS = 

rpcgen: $(RPCGENOBJS) $(CRT0) $(libs)
	$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(RPCGENOBJS) -o $@ $(LIBS)

rpcinfo: $(RPCINFOOBJS) $(CRT0) $(libs)
	$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(RPCINFOOBJS) -o $@ $(LIBS)


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
