# include/Makefile -- MiNTLib.
# Copyright (C) 1999-2001 Guido Flohr <guido@freemint.de>
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
csrcdir = $(top_srcdir)/mintlib
subdir = include

SUBDIRS = arpa bits mint net netinet nfs protocols rpc rpcsvc sys

default: all

include $(top_srcdir)/configvars
include $(top_srcdir)/bindist

# Make install-libs work.
LIBS =

all-here: features.h linker.h syscall-list.h

include $(top_srcdir)/phony

dont_install_libs = yes
include $(top_srcdir)/rules

GENSYS = AWK=$(AWK) $(csrcdir)/gensys 

# Special rule for features.h.  We build that automatically from
# features.h.in.
# If features.h would not change we won't replace it because that
# would cause a global rebuild.
features.h: features.h.in $(top_srcdir)/configvars
	@echo Updating features.h ...
	@rm -f $(srcdir)/features.tmp
	@betatag=`echo $(VERSION) | sed 's,[^A-Za-z]*\.[0-9][0-9]*,,'`; \
	major=`echo $(VERSION) | sed 's,\..*,,'`; \
	minor=`echo $(VERSION) | sed -e "s,^$$major\.,," -e 's,\..*,,' \
		-e 's,[^0-9]*$$,,'`; \
	revision=`echo $(VERSION) | sed -e "s,^$$major\.$$minor\.*,," \
		-e 's,[A-Za-z]$$,,'`; \
	test "$$revision" = "" && revision="0"; \
	test "$$betatag" = "" && betatag=\"\"; \
	sed -e "s,@MAJOR@,$$major,g" -e "s,@MINOR@,$$minor,g" \
	  -e "s,@REVISION@,$$revision,g" -e "s,@BETATAG@,$$betatag,g" \
	  $(srcdir)/features.h.in >$(srcdir)/features.tmp \
	  || exit 1;
	$(MOVEIFCHANGE) $(srcdir)/features.tmp $(srcdir)/features.h

# Special rule for linker.h.  We build that automatically from
# linker.h.in.
# If linker.h would not change we won't replace it because that
# would cause a global rebuild.
linker.h: linker.h.in $(top_srcdir)/configvars
	@echo Updating linker.h ...
	@rm -f $(srcdir)/linker.tmp
	@case $(LINKER_TYPE) in \
		GNU|OLD_GNU) ;; \
		*) echo "Unknown linker type $(LINKER_TYPE)" \
		   exit 1 \
		   ;; \
	esac
	@sed -e "s,@LINKER_TYPE@,$(LINKER_TYPE),g" \
	  $(srcdir)/linker.h.in >$(srcdir)/linker.tmp \
	  || exit 1;
	$(MOVEIFCHANGE) $(srcdir)/linker.tmp $(srcdir)/linker.h

syscall-list.h: $(csrcdir)/syscalls.list $(csrcdir)/gensys
	$(GENSYS) -header $(csrcdir)/syscalls.list >$@.tmp \
		&& $(MOVEIFCHANGE) $@.tmp $@

includefiles = $(filter %.h, $(MISCFILES)) stab.def COPYMINT COPYING.LIB \
syscall-list.h

install-include: remove-stale
	$(mkinstalldirs) $(includedir)
	@list='$(includefiles)'; for p in $$list; do \
  	  if test -f $$p; then \
	    echo " $(INSTALL) -m 644 $$p $(includedir)"; \
	    $(INSTALL) -m 644 $$p $(includedir); \
	  else :; fi; \
	done

ifeq (${HEADER_CLEANUP}, no)
remove-stale:
else
remove-stale:
	@echo "Renaming stale include files."
	CC=$(CC) MINTLIB_VERSION=$(VERSION) $(srcdir)/clean-include
endif

uninstall-include:
	@list='$(includefiles)'; \
	for p in $$list; do \
	  if test -f $$p; then \
	    echo " rm -f $(includedir)/$$p"; \
	    rm -f $(includedir)/$$p; \
	  else :; fi; \
	done

install-lib:

install-man:

uninstall-lib:

uninstall-man:
