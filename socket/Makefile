# socket/Makefile -- MiNTLib.
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
subdir = socket

include $(top_srcdir)/configvars
include $(top_srcdir)/bindist

# Make install-libs work.
LIBS = 

MANS = accept.3 bind.3 connect.3 getpeername.3 getrpcent.3 getsockname.3 \
getsockopt.3 listen.3 recv.3 recvfrom.3 recvmsg.3 resolver.5 send.3 sendmsg.3 \
sendto.3 setsockopt.3 shutdown.3 socket.3 socketpair.3

default: all

all-here:

# Missing: test_ifindex.c, tst-ether_aton.c.
TESTS = hton ntoa aton
include $(top_srcdir)/checkrules

check-local:

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

install-include:

uninstall-include:

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
	done;

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
	

