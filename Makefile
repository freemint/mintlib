# Makefile -- MiNTLib.
# Copyright (C) 1999-2001 Guido Flohr <guido@freemint.de>
# $Id$
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

MAKEFLAGS = -r
SHELL = /bin/sh

srcdir = .
top_srcdir = .

include $(top_srcdir)/configvars

-include /etc/sparemint/timezone
ifdef TIMEZONE
  LOCALTIME = $(TIMEZONE)
  POSIXRULES = $(TIMEZONE)
endif

SUBDIRS = include syscall startup conf crypt dirent gmp login mintlib misc \
  posix pwdgrp shadow signal socket stdiio stdio stdlib string sysvipc \
  termios time unix lib sunrpc tz
DIST_SUBDIRS = conf crypt dirent gmp include lib lib_g lib_p lib020 \
  login mintlib misc posix pwdgrp shadow signal socket startup \
  stdiio stdio stdlib string sunrpc syscall sysvipc termios time tz unix
TEST_SUBDIRS = crypt dirent login mintlib misc posix pwdgrp shadow signal \
  socket startup stdiio stdio stdlib string time tz unix

ifeq ($(WITH_PROFILE_LIB), yes)
  SUBDIRS += lib_p
endif

ifeq ($(WITH_DEBUG_LIB), yes)
  SUBDIRS += lib_g
endif

ifeq ($(WITH_020_LIB), yes)
  SUBDIRS += lib020
endif

include $(srcdir)/BINFILES
include $(srcdir)/SRCFILES
include $(srcdir)/MISCFILES
include $(srcdir)/EXTRAFILES

default: all

include phony

all: all-here all-recursive

all-here:

install: all-here install-recursive zoneswarning

uninstall: uninstall-recursive

install-lib: all install-lib-recursive

install-include: all install-include-recursive

install-man: all install-man-recursive

clean: clean-recursive
	rm -r .deps includepath CFILES

bakclean: bakclean-recursive

checkclean: checkclean-recursive

DISTFILES = $(MISCFILES) $(SRCFILES)
BINDISTFILES = $(MISCFILES) $(BINFILES)

distdir = mintlib-$(VERSION)
bindistdir = $(distdir)-bin
topdistdir = $(distdir)
topbindistdir = $(topdistdir)-bin

dist-check:
	@echo "WARNING: This will take VERY long and will consume"
	@echo "VERY much diskspace!!!"
	@$(MAKE) dist && tar xzf $(distdir).tar.gz && cd $(distdir) \
		&& $(MAKE) && $(MAKE) bin-dist \
		&& echo "##################################################" \
		&& echo "# $(distdir) is ready for distribution." \
		&& echo "##################################################"
	@rm -f $(distdir)

dist: $(top_srcdir)/CFILES $(top_srcdir)/include/linker.h \
  $(top_srcdir)/include/linker.h distdir
	-chmod -R a+r $(distdir)
	touch $(distdir)/include/features.h $(distdir)/include/linker.h
	GZIP=$(GZIP) $(TAR) chzf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)

distdir: $(DISTFILES)
	@if sed 15q $(srcdir)/NEWS | fgrep -e "$(VERSION)" > /dev/null; then :; else \
	  echo "NEWS not updated; not releasing" 1>&2; \
	  exit 1; \
	fi
	-rm -rf $(distdir)
	mkdir $(distdir)
	-chmod 777 $(distdir)
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  test -f $(distdir)/$$file \
	  || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	  || cp -p -r $$d/$$file $(distdir)/$$file; \
	done
	for subdir in $(DIST_SUBDIRS); do \
	  test -d $(distdir)/$$subdir \
	  || mkdir $(distdir)/$$subdir \
	  || exit 1; \
	  chmod 777 $(distdir)/$$subdir; \
	  (cd $$subdir && $(MAKE) top_distdir=../$(distdir) distdir=../$(distdir)/$$subdir distdir) \
	    || exit 1; \
	done

bin-dist: bindistdir
	-chmod -R a+r $(bindistdir)
	GZIP=$(GZIP) $(TAR) chzf $(bindistdir).tar.gz $(bindistdir)
	-rm -rf $(bindistdir)

bindistdir: $(BINDISTFILES)
	@if sed 15q $(srcdir)/NEWS | fgrep -e "$(VERSION)" > /dev/null; then :; else \
	  echo "NEWS not updated; not releasing" 1>&2; \
	  exit 1; \
	fi
	-rm -rf $(bindistdir)
	mkdir $(bindistdir)
	-chmod 777 $(bindistdir)
	@for file in $(BINDISTFILES); do \
	  d=$(srcdir); \
	  test -f $(bindistdir)/$$file \
	  || ln $$d/$$file $(bindistdir)/$$file 2> /dev/null \
	  || cp -p -r $$d/$$file $(bindistdir)/$$file; \
	done
	for subdir in $(DIST_SUBDIRS); do \
	  test "$$subdir" = "src" && continue; \
	  (cd $$subdir && $(MAKE) top_distdir=../$(bindistdir) binbasedir=../$(bindistdir) bindistdir) \
	    || exit 1; \
	done

all-recursive clean-recursive bakclean-recursive \
install-recursive uninstall-recursive install-lib-recursive \
install-include-recursive install-man-recursive uninstall-lib-recursive \
uninstall-include-recursive uninstall-man-recursive:
	@set fnord $(MAKEFLAGS); amf=$$2; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  target=`echo $@ | sed s/-recursive//`; \
	  echo "Making $$target in $$subdir"; \
	  (cd $$subdir && $(MAKE) $$target) \
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

dist-recursive bindist-recursive:
	@set fnord $(MAKEFLAGS); amf=$$2; \
	list='$(DIST_SUBDIRS)'; for subdir in $$list; do \
	  target=`echo $@ | sed s/-recursive//`; \
	  echo "Making $$target in $$subdir"; \
	  (cd $$subdir && $(MAKE) $$target) \
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

check-recursive checkclean-recursive:
	@set fnord $(MAKEFLAGS); amf=$$2; \
	list='$(TEST_SUBDIRS)'; for subdir in $$list; do \
	  target=`echo $@ | sed s/-recursive//`; \
	  echo "Making $$target in $$subdir"; \
	  (cd $$subdir && $(MAKE) $$target) \
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

help:
	@echo "This Makefile (and most of the Makefiles in the subdirectories)"
	@echo "supports the following main targets:"
	@echo 
	@echo "     help         show this help page (toplevel Makefile only)"
	@echo "     all          build everyting (default)"
	@echo "     install      install everything"
	@echo "     uninstall    uninstall all files"
	@echo "     zonenames    list possible values for time zone"
	@echo "	    check        build and run tests"
	@echo 
	@echo "The following targets are intended for use by the"
	@echo "maintainer:"
	@echo 
	@echo "     dist         make a source distribution (toplevel Makefile"
	@echo "                  only)"
	@echo "     bin-dist     make a binary distribution (toplevel Makefile"
	@echo "                  only)"
	@echo
	@echo "Please read the file INSTALL before running make.  Edit"
	@echo "the file configvars so that it matches the needs of "
	@echo "your site."

zonenames:
	cd $(top_srcdir)/tz && $(MAKE) zonenames

zoneswarning:
	@if test $(LOCALTIME) = Factory; then \
	  echo "WARNING: Installed tz database with localtime set to" ;\
	  echo "dummy time zone \`Factory'.  Run \`zic -l' with the" ;\
	  echo "correct timezone later or re-install after editing" ;\
	  echo "the \`LOCALTIME' variable in \`$(top_srcdir)/configvars." ;\
	fi
	@if test $(POSIXRULES) = America/New_York; then \
	  echo "WARNING: Installed tz database with posixrules set to" ;\
	  echo "dummy time zone \`Factory'.  Run \`zic -p' with the" ;\
	  echo "correct timezone later or re-install after editing" ;\
	  echo "the \`POSIXRULES' variable in \`$(top_srcdir)/configvars." ;\
	fi

check: check-recursive

00PatchLevel: 00PatchLevel.in configvars
	rm -f $@
	sed 's,@VERSION@,$(VERSION),g' $@.in >$@

mintlib.spec: mintlib.spec.in configvars
	rm -f $@
	sed 's,@VERSION@,$(VERSION),g' $@.in >$@

