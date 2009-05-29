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

OBJS = crt0.o gcrt0.o

libdir = $(prefix)/lib

INCLUDES = -nostdinc -I$(top_srcdir)/include

COMPILE = $(CC) $(WARN) $(CFLAGS) $(INCLUDES) $(DEFS)

all-here: $(OBJS)

include $(top_srcdir)/phony

crt0.o: $(srcdir)/crt0.S
	$(COMPILE) -c $< -o $@

gcrt0.o: $(srcdir)/crt0.S
	$(COMPILE) -DGCRT0 -c $< -o $@

include $(top_srcdir)/rules

install: all-here
	$(mkinstalldirs) $(libdir)
	@list='$(OBJS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(INSTALL) -m 644 $$p $(libdir)"; \
	    $(INSTALL) -m 644 $$p $(libdir); \
	  else :; fi; \
	done

uninstall:
	@list='$(OBJS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " rm -f $(libdir)/$$p"; \
	    rm -f $(libdir)/$$p; \
	  else :; fi; \
	done
	
install-include:

install-man:

uninstall-include:

uninstall-man:

checkclean:

