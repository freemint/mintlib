# include/net/Makefile -- MiNTLib.
# Copyright (C) 1999 Guido Flohr <guido@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

SHELL = /bin/sh

srcdir = .
top_srcdir = ../..
csrcdir = $(top_srcdir)/src
subdir = net

include $(top_srcdir)/configvars
include $(top_srcdir)/bindist

# Make install-libs work.
LIBS =

default: all

all-here:

include $(top_srcdir)/phony

dont_install_libs = yes
include $(top_srcdir)/rules

includefiles = $(filter %.h, $(MISCFILES))

install-include: 
	$(mkinstalldirs) $(includedir)/net
	@list='$(includefiles)'; for p in $$list; do \
  	  if test -f $$p; then \
	    echo " $(INSTALL) -m 644 $$p $(includedir)/net"; \
	    $(INSTALL) -m 644 $$p $(includedir)/net; \
	  else :; fi; \
	done
	
uninstall-include:
	@list='$(includefiles)'; \
	for p in $$list; do \
	  if test -f $$p; then \
	    echo " rm -f $(includedir)/net/$$p"; \
	    rm -f $(includedir)/net/$$p; \
	  else :; fi; \
	done

install-lib:

install-man:

uninstall-lib:

uninstall-man:
