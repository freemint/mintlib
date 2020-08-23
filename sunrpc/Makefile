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

rpcsvc = bootparam_prot.x mount.x rex.x rusers.x yppasswd.x key_prot.x \
nfs_prot.x rquota.x sm_inter.x klm_prot.x nlm_prot.x rstat.x spray.x
rpcsvc_hdrs = $(rpcsvc:.x=.h)
rpcsvc_funcs = $(addprefix x, $(rpcsvc:.x=.c))

ifndef CROSS
all-here: rpcgen rpcinfo $(rpcsvc_hdrs:.h=.stmp) $(rpcsvc_funcs:.c=.stmp)
else
all-here: rpcgen rpcinfo
endif

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

# FIXME: Tests still missing.
TESTS = dummy
include $(top_srcdir)/checkrules

# Override test flags.
cflags = -O -Wall
type = 

RPCGENOBJS = $(RPCGENSRCFILES:.c=.o)
RPCINFOOBJS = $(RPCINFOSRCFILES:.c=.o)

MANS = bindresvport.3 getrpcport.3 rpc.3 rpc.5 rpcgen.1 rpcinfo.8 xdr.3 
DOCS = 

rpcgen: $(RPCGENOBJS) $(CRT0) $(libs)
	$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(RPCGENOBJS) -o $@ $(LIBS)

rpcinfo: $(RPCINFOOBJS) $(CRT0) $(libs)
	$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(RPCINFOOBJS) -o $@ $(LIBS)

install: all-here install-rpcsvc-programs install-rpcsvc-headers

uninstall: uninstall-rpcsvc-programs uninstall-rpcsvc-headers

# Not suitable for cross-compiling.
ifndef CROSS

rpcgen-cmd := $(srcdir)/rpcgen -Y $(patsubst %/cpp,%,$(shell which cpp))

# XDR headers.
$(rpcsvc:%.x=%.h): %.h: %.stmp
	@:
%.stmp: %.x rpcgen
	-@rm -f $(@stmp=T) $@
	$(rpcgen-cmd) -h $< -o $(@:stmp=T)
	$(MOVEIFCHANGE) $(@:stmp=T) $(@:stmp=h)
	touch $@

# XDR functions.
$(rcpsvc:%.x=x%.c): x%.c: x%.stmp
	@:
x%.stmp: %.x rpcgen
	-@rm -f $(@:stmp=T) $@
	$(rpcgen-cmd) -c $< -o $(@:stmp=T)
	$(MOVEIFCHANGE) $(@:stmp=T) $(@:stmp=c)
	touch $@

install-rpcsvc-programs: rpcgen rpcinfo
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	$(INSTALL) -m 755 rpcgen $(DESTDIR)$(bindir)
	$(mkinstalldirs) $(DESTDIR)$(sbindir)
	$(INSTALL) -m 755 rpcinfo $(DESTDIR)$(sbindir)

uninstall-rpcsvc-programs:
	rm -f $(DESTDIR)$(bindir)/rpcgen
	rm -f $(DESTDIR)$(sbindir)/rpcinfo

# End of non-cross section.
else
# Cross section

install-rpcsvc-programs:

uninstall-rpcsvc-programs:

# End of cross section
endif

ifndef CROSS
install-rpcsvc-headers: $(rpcsvc_hdrs:.h=.stmp)
else
install-rpcsvc-headers:
endif
	$(mkinstalldirs) $(DESTDIR)$(includedir)/rpcsvc
	for header in $(rpcsvc_hdrs); do \
	  echo "$(INSTALL) -m 644 $$header $(includedir)/rpcsvc"; \
	  $(INSTALL) -m 644 $$header $(DESTDIR)$(includedir)/rpcsvc; \
	done; 

ifndef CROSS
uninstall-rpcsvc-headers: $(rpcsvc_hdrs:.h=.stmp)
else
uninstall-rpcsvc-headers:
endif
	for header in $(rpcsvc_hdrs); do \
	  echo "rm -f $(includedir)/rpcsvc/$$header"; \
	  rm -f $(DESTDIR)$(includedir)/rpcsvc/$$header; \
	done; 

install-man:
	sections=""; \
	for manpage in $(MANS); do \
	  sections="$$sections $(mandir)/man`echo $$manpage | sed 's,^.*\\.,,'`"; \
	done; \
	mandirs=`echo $$sections | sort | uniq`; \
	for mandir in $$mandirs; do \
	  $(mkinstalldirs) $(DESTDIR)$$mandir; \
	done; \
	for manpage in $(MANS); do \
	  section=`echo $$manpage | sed 's,^.*\\.,,'`; \
	  echo "$(INSTALL) -m 644 $$manpage $(mandir)/man$$section"; \
	  $(INSTALL) -m 644 $$manpage $(DESTDIR)$(mandir)/man$$section; \
	done;

uninstall-man:
	@for manpage in $(MANS); do \
	  section=`echo $$manpage | sed 's,^.*\\.,,'`; \
	  echo "rm -f $(mandir)/man$$section/$$manpage"; \
	  echo "rm -f $(mandir)/man$$section/$$manpage.gz"; \
	  echo "rm -f $(mandir)/man$$section/$$manpage.Z"; \
	  rm -f $(DESTDIR)$(mandir)/man$$section/$$manpage; \
	  rm -f $(DESTDIR)$(mandir)/man$$section/$$manpage.gz; \
	  rm -f $(DESTDIR)$(mandir)/man$$section/$$manpage.Z; \
	done

