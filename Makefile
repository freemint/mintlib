# Makefile -- MiNTLib.
# Copyright (C) 1999-2001 Guido Flohr <guido@freemint.de>
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

SUBDIRS = include syscall startup argp conf crypt dirent gmp login mintlib \
  misc multibyte posix pwdgrp shadow signal socket stdiio stdio stdlib \
  string sysvipc termios time unix
DIST_SUBDIRS = argp conf crypt dirent gmp include \
  login mintlib misc multibyte posix pwdgrp shadow signal socket startup \
  stdiio stdio stdlib string sunrpc syscall sysvipc termios time tz unix
TEST_SUBDIRS = argp crypt dirent login mintlib misc posix pwdgrp shadow signal \
  socket startup stdiio stdio stdlib string time tz unix

BASE_FLAVOURS = m68000
ifeq ($(WITH_020_LIB), yes)
  BASE_FLAVOURS += m68020
endif
ifeq ($(WITH_V4E_LIB), yes)
  BASE_FLAVOURS += coldfire
endif
FLAVOURS = $(BASE_FLAVOURS)

ifeq ($(WITH_PROFILE_LIB), yes)
  FLAVOURS += $(addsuffix -profile,$(BASE_FLAVOURS))
endif
ifeq ($(WITH_DEBUG_LIB), yes)
  FLAVOURS += $(addsuffix -debug,$(BASE_FLAVOURS))
endif
ifeq ($(WITH_FASTCALL), yes)
  FLAVOURS += $(addsuffix -fastcall,$(BASE_FLAVOURS))
endif

LIBDIRS += $(addprefix build/,$(FLAVOURS))

SUBDIRS += $(LIBDIRS)
# must come after lib dirs, since it needs the just-built library
SUBDIRS += tz sunrpc

include $(srcdir)/BINFILES
include $(srcdir)/SRCFILES
include $(srcdir)/MISCFILES
include $(srcdir)/EXTRAFILES

default: all

include phony

all: all-here all-recursive

# the SRCFILES, EXTRAFILES, and MISCFILES are still required by
# the rules; FIXME
all-here: $(top_srcdir)/includepath
	@for flavour in $(FLAVOURS); do \
	   dir=build/$$flavour; \
	   mkdir -p $$dir/.deps; \
	   test -f $$dir/SRCFILES || touch $$dir/SRCFILES; \
	   test -f $$dir/EXTRAFILES || touch $$dir/EXTRAFILES; \
	   test -f $$dir/MISCFILES || touch $$dir/MISCFILES; \
	   cflags=""; \
	   nocflags=""; \
	   qualifier=""; \
	   cflags=""; \
	   for f in `echo $$flavour | sed -e 's/-/ /g'`; do \
	     case $$f in \
	     profile) \
	     	qualifier=_p; \
	     	nocflags="-fomit-frame-pointer"; \
	        cflags="$$cflags $(CFLAGS_profile)"; \
	     	;; \
	     debug) \
	        qualifier=_g; \
	        nocflags="-O2 -O3 -fomit-frame-pointer -fexpensive-optimizations"; \
	        cflags="$$cflags $(CFLAGS_debug)"; \
	        ;; \
	     m68000) \
	        cflags="$$cflags $(CFLAGS_m68000)"; \
	        ;; \
	     m68020) \
	        cflags="$$cflags $(CFLAGS_m68020)"; \
	        ;; \
	     coldfire) \
	        cflags="$$cflags $(CFLAGS_coldfire)"; \
	        ;; \
	     short) \
	        cflags="$$cflags $(CFLAGS_short)"; \
	        ;; \
	     fastcall) \
	        cflags="$$cflags $(CFLAGS_fastcall)"; \
	        ;; \
	     esac; \
	   done; \
	   instdir=`$(CC) $$cflags -print-multi-directory`; \
	   test -f $$dir/BINFILES || echo "BINFILES = libc$${qualifier}.a libiio$${qualifier}.a" > $$dir/BINFILES; \
	   ( echo "SHELL = /bin/sh"; \
	     echo "srcdir = ."; \
	     echo "top_srcdir = ../.."; \
	     echo "subdir = $$dir"; \
	     echo "qualifier = $$qualifier"; \
	     echo "cflags = $$cflags"; \
	     echo "nocflags = $$nocflags"; \
	     echo "instdir = $$instdir"; \
	     echo ""; \
	     echo "default: all"; \
	     echo ""; \
	     echo 'include $$(top_srcdir)/buildrules'; \
	   ) > $$dir/Makefile; \
	done

install: all-here install-recursive zoneswarning

uninstall: uninstall-recursive

install-lib: all install-lib-recursive

install-include: all install-include-recursive

install-headers: install-headers-recursive

install-man: all install-man-recursive

clean:: clean-recursive
	rm -rf .deps includepath CFILES build

distclean:: distclean-recursive

bakclean: bakclean-recursive

checkclean: checkclean-recursive

DISTFILES = $(MISCFILES) $(SRCFILES)
BINDISTFILES = $(MISCFILES) $(BINFILES)

distdir = mintlib-$(VERSION)
bindistdir = $(distdir)-bin
topdistdir = $(distdir)
topbindistdir = $(topdistdir)-bin

$(top_srcdir)/includepath: $(top_srcdir)/configvars
	@echo "Generating $@"; \
	installdir=`$(CC) --print-search-dirs | awk '{ print $$2; exit; }'`; \
	echo "$${installdir}include -I$${installdir}include-fixed" >$@
	@if [ -z "$$(<$@)" ]; then \
	  rm $@; \
	  echo "error: The syntax \$$(<file) is unsupported by $(SHELL)." >&2; \
	  echo "       Please use \"$(MAKE) SHELL=/bin/bash\" instead." >&2; \
	  exit 1; \
	fi
	
dist-check:
	@echo "WARNING: This will take VERY long and will consume"
	@echo "VERY much diskspace!!!"
	@$(MAKE) dist && tar xzf $(distdir).tar.gz && cd $(distdir) \
		&& $(MAKE) && $(MAKE) bin-dist \
		&& echo "##################################################" \
		&& echo "# $(distdir) is ready for distribution." \
		&& echo "##################################################"
	@rm -rf $(distdir)

dist: $(top_srcdir)/CFILES $(top_srcdir)/include/features.h \
  $(top_srcdir)/include/linker.h distdir
	-chmod -R a+r $(distdir)
	touch $(distdir)/include/features.h $(distdir)/include/linker.h
	GZIP=$(GZIP) $(TAR) chzf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)

distdir: $(DISTFILES)
	@if sed 15q $(srcdir)/ChangeLog | fgrep -e "$(VERSION)" > /dev/null; then :; else \
	  echo "ChangeLog not updated; not releasing" 1>&2; \
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
	@if sed 15q $(srcdir)/ChangeLog | fgrep -e "$(VERSION)" > /dev/null; then :; else \
	  echo "ChangeLog not updated; not releasing" 1>&2; \
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

all-recursive clean-recursive distclean-recursive bakclean-recursive \
install-recursive uninstall-recursive \
install-include-recursive install-man-recursive \
uninstall-include-recursive uninstall-man-recursive:
	@set fnord $(MAKEFLAGS); amf=$$2; \
	echo $@ | grep -q install; \
	if test $$? = 0 -a "${CROSS}" = yes -a "$(DESTDIR)${prefix}" = "/usr"; then \
	   echo "attempting to install on host; aborting" >&2; \
           exit 1; \
	fi; \
	list='$(SUBDIRS)'; \
	if test "$@" = clean-recursive; then list='$(filter-out $(LIBDIRS),$(SUBDIRS))'; fi; \
	if test "$@" = distclean-recursive; then list='$(filter-out $(LIBDIRS),$(SUBDIRS))'; fi; \
	for subdir in $$list; do \
	  target=`echo $@ | sed s/-recursive//`; \
	  echo "Making $$target in $$subdir"; \
	  (cd $$subdir && $(MAKE) $$target) \
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

install-lib-recursive uninstall-lib-recursive:
	echo $@ | grep -q install; \
	if test $$? = 0 -a "${CROSS}" = yes -a "$(DESTDIR)${prefix}" = "/usr"; then \
	   echo "attempting to install on host; aborting" >&2; \
           exit 1; \
	fi; \
	list='$(LIBDIRS)'; \
	for subdir in $$list; do \
	  target=`echo $@ | sed s/-recursive//`; \
	  echo "Making $$target in $$subdir"; \
	  $(MAKE) -C $$target $$subdir || exit 1; \
	done

install-headers-recursive:
	if test "${CROSS}" = yes -a "$(DESTDIR)${prefix}" = "/usr"; then \
	   echo "attempting to install on host; aborting" >&2; \
           exit 1; \
	fi; \
	$(MAKE) -C syscall all || exit 1; \
	list='include sunrpc'; \
	for subdir in $$list; do \
	  target=`echo $@ | sed s/-recursive//`; \
	  echo "Making $$target in $$subdir"; \
	  $(MAKE) -C $$subdir $$target || exit 1; \
	done

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

