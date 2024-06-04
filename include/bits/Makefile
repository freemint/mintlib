# include/bits/Makefile -- MiNTLib.
# Copyright (C) 2000 Guido Flohr <guido@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

SHELL = /bin/sh

srcdir = .
top_srcdir = ../..
subdir = bits

include $(top_srcdir)/configvars
include $(top_srcdir)/bindist

SUBDIRS = types

# Make install-libs work.
LIBS =

default: all

all-here:

include $(top_srcdir)/phony

include $(top_srcdir)/rules

includefiles = $(filter %.h, $(MISCFILES))

install-include install-headers:
	$(mkinstalldirs) $(DESTDIR)$(includedir)/$(subdir)
	@list='$(includefiles)'; for p in $$list; do \
  	  if test -f $$p; then \
	    echo " $(INSTALL) -m 644 $$p $(includedir)/$(subdir)"; \
	    $(INSTALL) -m 644 $$p $(DESTDIR)$(includedir)/$(subdir); \
	  else :; fi; \
	done
	@for subdir in $(SUBDIRS); do \
	  echo "Making $@ in $$subdir"; \
	  $(MAKE) -C $$subdir $@ || exit 1; \
	done
	
uninstall-include:
	@list='$(includefiles)'; \
	for p in $$list; do \
	  if test -f $$p; then \
	    echo " rm -f $(includedir)/$(subdir)/$$p"; \
	    rm -f $(DESTDIR)$(includedir)/$(subdir)/$$p; \
	  else :; fi; \
	done
	@for subdir in $(SUBDIRS); do \
	  echo "Making $@ in $$subdir"; \
	  $(MAKE) -C $$subdir $@; \
	done

install-lib:

install-man:

uninstall-lib:

uninstall-man:
