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

INCLUDES = -nostdinc -I$(top_srcdir)/include -I$(top_srcdir)/mintlib

COMPILE = $(CC) $(WARN) $(CFLAGS) $(INCLUDES) $(DEFS)

all-here: $(OBJS)

include $(top_srcdir)/phony

crt0.o: $(srcdir)/crt0.S
	$(COMPILE) $(INCLUDES) -c $< -o $@

gcrt0.o: $(srcdir)/crt0.S
	$(COMPILE) $(INCLUDES) -DGCRT0 -c $< -o $@

include $(top_srcdir)/rules

install: all-here
	$(mkinstalldirs) $(DESTDIR)$(libdir)
	@list='$(OBJS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(INSTALL) -m 644 $$p $(libdir)"; \
	    $(INSTALL) -m 644 $$p $(DESTDIR)$(libdir); \
	  else :; fi; \
	done

uninstall:
	@list='$(OBJS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " rm -f $(libdir)/$$p"; \
	    rm -f $(DESTDIR)$(libdir)/$$p; \
	  else :; fi; \
	done
	
install-include:

install-man:

uninstall-include:

uninstall-man:

checkclean:

