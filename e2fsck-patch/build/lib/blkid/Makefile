# Makefile for libblkid
#
# Copyright (C) 2001 Theodore Ts'o (tytso@mit.edu)
#
# This file can be redistributed under the terms of the
# GNU Lesser General Public License

srcdir = ../../../lib/blkid
top_srcdir = ../../..
VPATH = ../../../lib/blkid
top_builddir = ../..
my_dir = lib/blkid
INSTALL = /usr/bin/install -c

# Beginning of file MCONFIG

all::

check::

fullcheck::

SHELL = /bin/sh

COMPRESS_EXT = gz bz2 bz Z

prefix = /usr
root_prefix = 
exec_prefix = ${prefix}
root_bindir = ${root_prefix}/bin
root_sbindir = ${root_prefix}/sbin
root_libdir = ${root_prefix}/lib
datarootdir = ${prefix}/share
bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libdir = ${exec_prefix}/lib
datadir= ${datarootdir}
localedir = $(datadir)/locale
root_sysconfdir= ${root_prefix}/etc
includedir = ${prefix}/include
mandir = ${datarootdir}/man
man1dir = $(mandir)/man1
man3dir = $(mandir)/man3
man5dir = $(mandir)/man5
man8dir = $(mandir)/man8
infodir = ${datarootdir}/info
datadir = ${datarootdir}
pkgconfigdir = $(libdir)/pkgconfig



 V =
 ifeq ($(strip $(V)),)
 #  E = @echo
 #  ES = echo
 #  Q = @
    E = @echo
    ES = echo
    Q = @
 else
    E = @\#
    ES = \#
    Q =
 endif

# E = @echo
# ES = echo
# Q = @

 CHECK=sparse
 CHECK_OPTS=-Wsparse-all -Wno-transparent-union -Wno-return-void -Wno-undef -Wno-non-pointer-null
 CPPCHECK=cppcheck
 CPPCHECK_OPTS=--force --enable=all --quiet
 ifeq ("$(C)", "2")
   CHECK_CMD=$(CHECK) $(CHECK_OPTS) -Wbitwise -D__CHECK_ENDIAN__
   CPPCHECK_CMD=$(CPPCHECK) $(CPPCHECK_OPTS)
 else
   ifeq ("$(C)", "1")
     CHECK_CMD=$(CHECK) $(CHECK_OPTS)
     CPPCHECK_CMD=$(CPPCHECK) $(CPPCHECK_OPTS)
    else
     CHECK_CMD=@true
     CPPCHECK_CMD=@true
   endif
 endif

# CHECK_CMD=true
# CPPCHECK_CMD=true

CC = gcc
BUILD_CC = gcc
CFLAGS = -g -O2
CFLAGS_SHLIB = -g -O2
CFLAGS_STLIB = -g -O2
CPPFLAGS = -I. -I$(top_builddir)/lib -I$(top_srcdir)/lib
ALL_CFLAGS = $(CPPFLAGS) $(CFLAGS) $(CFLAGS_WARN) -DHAVE_CONFIG_H $(LOCAL_CFLAGS)
ALL_CFLAGS_SHLIB = $(CPPFLAGS) $(CFLAGS_SHLIB) $(CFLAGS_WARN) -DHAVE_CONFIG_H $(LOCAL_CFLAGS)
ALL_CFLAGS_STLIB = $(CPPFLAGS) $(CFLAGS_STLIB) $(CFLAGS_WARN) -DHAVE_CONFIG_H $(LOCAL_CFLAGS)
LDFLAGS = 
LDFLAGS_SHLIB = 
ALL_LDFLAGS = $(LDFLAGS) 
LDFLAGS_STATIC =  -static
BUILD_CFLAGS = -g -O2  -I. -I$(top_builddir)/lib -I$(top_srcdir)/lib -DHAVE_CONFIG_H
BUILD_LDFLAGS = 
RDYNAMIC = -rdynamic
LINK_BUILD_FLAGS = 
LINK_INSTALL_FLAGS = -f
RM = /bin/rm
LN = /bin/ln
LN_S = ln -s
MV = /bin/mv
CP = /bin/cp
CHMOD = /bin/chmod
AR = ar
AWK = mawk
SED = /bin/sed
PERL = /usr/bin/perl
RANLIB = ranlib
STRIP = strip
LD = $(PURE) gcc
ARUPD = $(AR) r
ARGEN = $(AR) rc
LDCONFIG = /sbin/ldconfig
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
MKINSTALLDIRS = $(top_builddir)/../config/mkinstalldirs

#
# Library definitions
#
LIB = $(top_builddir)/lib
LIBSS = $(LIB)/libss.a  -ldl
LIBCOM_ERR = $(LIB)/libcom_err.a  -lpthread
LIBE2P = $(LIB)/libe2p.a
LIBEXT2FS = $(LIB)/libext2fs.a
LIBUUID = -luuid   
LIBMAGIC = -ldl
LIBFUSE = 
LIBSUPPORT = $(LIBINTL) $(LIB)/libsupport.a
LIBBLKID = $(LIB)/libblkid.a  $(LIBUUID)
LIBINTL = 
SYSLIBS = 
DEPLIBSS = $(LIB)/libss.a
DEPLIBCOM_ERR = $(LIB)/libcom_err.a
DEPLIBUUID = 
DEPLIBSUPPORT = $(LIB)/libsupport.a
DEPLIBBLKID = $(LIB)/libblkid.a  $(DEPLIBUUID)
TESTENV = LD_LIBRARY_PATH="$(LIB):$${LD_LIBRARY_PATH}" DYLD_LIBRARY_PATH="$(LIB):$${DYLD_LIBRARY_PATH}"

STATIC_LIBSS = $(LIB)/libss.a -ldl
STATIC_LIBCOM_ERR = $(LIB)/libcom_err.a -lpthread
STATIC_LIBE2P = $(LIB)/libe2p.a
STATIC_LIBEXT2FS = $(LIB)/libext2fs.a
STATIC_LIBUUID = -luuid   
STATIC_LIBSUPPORT = $(LIBINTL) $(LIBSUPPORT)
STATIC_LIBBLKID = $(LIB)/libblkid.a $(STATIC_LIBUUID)
DEPSTATIC_LIBSS = $(LIB)/libss.a
DEPSTATIC_LIBCOM_ERR = $(LIB)/libcom_err.a
DEPSTATIC_LIBUUID = 
DEPSTATIC_LIBSUPPORT = $(DEPLIBSUPPORT)
DEPSTATIC_LIBBLKID = $(LIB)/libblkid.a $(DEPSTATIC_LIBUUID)

PROFILED_LIBSS = $(LIB)/libss.a -ldl
PROFILED_LIBCOM_ERR = $(LIB)/libcom_err.a -lpthread
PROFILED_LIBE2P = $(LIB)/libe2p.a
PROFILED_LIBEXT2FS = $(LIB)/libext2fs.a
PROFILED_LIBUUID = -luuid   
PROFILED_LIBSUPPORT = $(LIBINTL) $(LIB)/libsupport.a
PROFILED_LIBBLKID = $(LIB)/libblkid.a $(PROFILED_LIBUUID)
DEPPROFILED_LIBSS = $(LIB)/libss.a
DEPPROFILED_LIBCOM_ERR = $(LIB)/libcom_err.a
DEPPROFILED_LIBUUID = -luuid  
DEPPROFILED_LIBSUPPORT = $(PROFILED_LIBSUPPORT)
DEPPROFILED_LIBBLKID = $(LIB)/libblkid.a $(DEPPROFILED_LIBUUID)

#
# A fast substitution command for fixing up man pages, shell scripts, etc.
#
SUBST_CONF=$(top_builddir)/util/subst.conf
SUBSTITUTE= $(top_builddir)/util/subst -f $(SUBST_CONF)
SUBSTITUTE_UPTIME= $(top_builddir)/util/subst -t -f $(SUBST_CONF)
DEP_SUBSTITUTE= $(top_builddir)/util/subst $(SUBST_CONF)

$(top_builddir)/util/subst:
	cd $(top_builddir)/util ; $(MAKE) subst

#
# Script for installing symlinks (for shared libraries)
#
$(top_builddir)/util/install-symlink: $(top_srcdir)/util/install-symlink.in \
			      $(top_builddir)/config.status
	cd $(top_builddir); CONFIG_FILES=util/install-symlink ./config.status
	chmod +x $(top_builddir)/util/install-symlink

$(top_builddir)/util/symlinks:
	cd $(top_builddir)/util ; $(MAKE) symlinks

INSTALL_SYMLINK = /bin/sh $(top_builddir)/util/install-symlink \
			 \
			--symlinks=$(top_builddir)/util/symlinks
DEP_INSTALL_SYMLINK = $(top_builddir)/util/install-symlink \
			$(top_builddir)/util/symlinks

#
# Warning flags
#
# Run make gcc-wall to do a build with warning messages.
#
#
WFLAGS=		-std=gnu99 -D_XOPEN_SOURCE=600 -D_GNU_SOURCE \
			-pedantic $(WFLAGS_EXTRA) \
			-Wall -W -Wwrite-strings -Wpointer-arith \
			-Wcast-qual -Wcast-align -Wno-variadic-macros \
			-Wstrict-prototypes -Wmissing-prototypes \
			-Wformat-security  -Wformat-nonliteral \
			-Wmissing-format-attribute -O2 -Wstrict-aliasing \
			-Wnested-externs -Winline -DNO_INLINE_FUNCS -Wshadow \
			-UENABLE_NLS

gcc-wall-new:
	($(MAKE) CFLAGS_WARN="$(WFLAGS)" > /dev/null) 2>&1 | sed -f $(top_srcdir)/util/gcc-wall-cleanup

gcc-wall:
	$(MAKE) clean > /dev/null
	$(MAKE) gcc-wall-new

static-check:
	($(MAKE) C=1 V=1 CFLAGS="$(ALL_CFLAGS) $(WFLAGS)") 2>&1 | sed -f $(top_srcdir)/util/static-analysis-cleanup

static-check-all:
	$(MAKE) clean > /dev/null
	$(MAKE) static-check

#
# Installation user and groups
#
BINGRP=		bin
BINOWN=		bin
BINMODE=	555
INCGRP=		bin
INCOWN=		bin
INCMODE=	444
LIBOWN=		bin
LIBGRP=		bin
LIBMODE=	444
MANGRP=		bin
MANOWN=		bin
MANMODE=	444

#
# Autoconf magic...
#

DEP_LIB_MAKEFILES = $(top_srcdir)/lib/Makefile.library \
	$(top_srcdir)/lib/Makefile.elf-lib  \
	$(top_srcdir)/lib/Makefile.bsd-lib \
	$(top_srcdir)/lib/Makefile.darwin-lib \
	$(top_srcdir)/lib/Makefile.solaris-lib \
	$(top_srcdir)/lib/Makefile.profile

$(top_builddir)/config.status: $(top_srcdir)/configure
	cd $(top_builddir); ./config.status --recheck

$(top_builddir)/MCONFIG: $(top_srcdir)/MCONFIG.in $(top_builddir)/config.status
	cd $(top_builddir); CONFIG_FILES=MCONFIG ./config.status

$(top_builddir)/lib/config.h: $(top_srcdir)/lib/config.h.in \
			      $(top_builddir)/config.status
	cd $(top_builddir); CONFIG_FILES=lib/config.h ./config.status

$(top_builddir)/lib/dirpaths.h: $(DEP_SUBSTITUTE) $(top_srcdir)/lib/dirpaths.h.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE) $(top_srcdir)/lib/dirpaths.h.in $@

$(top_builddir)/lib/substitute_sh: $(top_srcdir)/lib/substitute_sh.in \
		$(top_builddir)/config.status
	cd $(top_builddir); CONFIG_FILES=lib/substitute_sh ./config.status

$(top_builddir)/util/subst.conf: $(top_srcdir)/util/subst.conf.in \
		$(top_builddir)/config.status
	cd $(top_builddir); CONFIG_FILES=util/subst.conf ./config.status

Makefile: $(srcdir)/Makefile.in $(top_builddir)/MCONFIG \
		$(DEP_MAKEFILE) $(top_builddir)/config.status
	cd $(top_builddir); CONFIG_FILES=$(my_dir)/Makefile ./config.status

#$(top_srcdir)/configure: $(top_srcdir)/configure.ac
#	cd $(top_srcdir) && autoheader && autoconf

coverage.txt: Makefile $(SRCS)
	if test -n "$(SRCS)"; then \
		gcov -s $(top_srcdir) -o . $(SRCS) > coverage.txt 2>&1 ; \
	fi

clean::
	$(RM) -f *.gcda *.gcov *.gcno coverage.txt

#
# Make depend magic...
#

.depend: Makefile $(SRCS) $(top_srcdir)/depfix.sed $(top_srcdir)/wordwrap.pl
	if test -n "$(SRCS)" ; then \
		$(CC) -M $(ALL_CFLAGS) $(DEPEND_CFLAGS) $(SRCS) | \
			$(SED) -f $(top_srcdir)/depfix.sed \
			    -e 's; $(srcdir)/; $$(srcdir)/;g' \
			    -e 's; $(top_srcdir)/; $$(top_srcdir)/;g' \
			    -e 's; $(top_builddir)/; $$(top_builddir)/;g' \
			    -e 's; \./; ;g' \
			    -e '/^#/d' \
			    -e '/^ *\\$$/d' | \
			$(PERL) $(top_srcdir)/wordwrap.pl > .depend; \
	else :; fi

depend:: .depend
	if test -n "$(SRCS)" ; then \
		sed -e '/^# +++ Dependency line eater +++/,$$d' \
			< $(srcdir)/Makefile.in | cat - .depend \
			> $(srcdir)/Makefile.in.new; \
	if cmp -s $(srcdir)/Makefile.in $(srcdir)/Makefile.in.new ; then \
		$(RM) $(srcdir)/Makefile.in.new ; \
	else \
		$(MV) $(srcdir)/Makefile.in $(srcdir)/Makefile.in.old; \
		$(MV) $(srcdir)/Makefile.in.new $(srcdir)/Makefile.in; \
	fi ; else :; fi

# End of file MCONFIG

all:: 

SMANPAGES=	libblkid.3

OBJS= cache.o dev.o devname.o devno.o getsize.o llseek.o probe.o \
 read.o resolve.o save.o tag.o version.o 

SRCS= $(srcdir)/cache.c $(srcdir)/dev.c $(srcdir)/devname.c $(srcdir)/devno.c \
 $(srcdir)/getsize.c $(srcdir)/llseek.c $(srcdir)/probe.c \
 $(srcdir)/read.c $(srcdir)/resolve.c $(srcdir)/save.c $(srcdir)/tag.c \
 $(srcdir)/version.c

HFILES_IN=	blkid.h blkid_types.h

LIBRARY= libblkid
LIBDIR= blkid

ELF_VERSION = 1.0
ELF_SO_VERSION = 1
ELF_IMAGE = libblkid
ELF_MYDIR = blkid
ELF_INSTALL_DIR = $(root_libdir)
ELF_OTHER_LIBS = -luuid

BSDLIB_VERSION = 2.0
BSDLIB_IMAGE = libblkid
BSDLIB_MYDIR = blkid
BSDLIB_INSTALL_DIR = $(root_libdir)

all:: subdirs $(LIBRARY).a

install-shlibs::

uninstall-shlibs::

real-subdirs::

subdirs:: Makefile
	$(Q) $(MAKE) -s real-subdirs
	$(Q) touch subdirs

clean::
	$(Q) $(RM) -f subdirs

$(LIBRARY).a: $(OBJS)
	$(E) "	GEN_LIB $@"
	$(Q) (if test -r $@; then $(RM) -f $@.bak && $(MV) $@ $@.bak; fi)
	$(Q) $(ARGEN) $@ $(OBJS)
	-@$(RANLIB) $@
	$(Q) $(RM) -f ../$@
	$(Q) (cd ..; $(LN) $(LINK_BUILD_FLAGS) \
		`echo $(my_dir) | sed -e 's;lib/;;'`/$@ $@)

$(LIB)/$(LIBRARY).a: $(LIBRARY).a

LIBS_BLKID=	$(STATIC_LIBBLKID) $(STATIC_LIBUUID)
DEPLIBS_BLKID=	$(DEPSTATIC_LIBBLKID) $(DEPSTATIC_LIBUUID)

.c.o:
	$(E) "	CC $<"
	$(Q) $(CC) $(ALL_CFLAGS_STLIB) -c $< -o $@
	$(Q) $(CHECK_CMD) $(ALL_CFLAGS) $<
	$(Q) $(CPPCHECK_CMD) $(CPPFLAGS) $<
#	$(Q) $(CC) $(ALL_CFLAGS_STLIB) -g -pg -o profiled/$*.o -c $<
#	$(Q) $(CC) $(ALL_CFLAGS_SHLIB) -fPIC -shared -o elfshared/$*.o -c $<
#	$(Q) $(CC) $(ALL_CFLAGS_SHLIB) $(BSDLIB_PIC_FLAG) -o pic/$*.o -c $<

all:: $(SMANPAGES) blkid.pc

blkid_types.h: $(srcdir)/blkid_types.h.in $(top_builddir)/config.status
	$(E) "	CONFIG.STATUS $@"
	$(Q) cd $(top_builddir); \
		CONFIG_FILES=$(my_dir)/blkid_types.h ./config.status

blkid.h: $(srcdir)/blkid.h.in
	$(E) "	CP $@"
	$(Q) cp $(srcdir)/blkid.h.in blkid.h

libblkid.3: $(DEP_SUBSTITUTE) $(srcdir)/libblkid.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/libblkid.3.in libblkid.3

tst_cache: $(srcdir)/cache.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_cache -DTEST_PROGRAM $(srcdir)/cache.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_dev: $(srcdir)/dev.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_dev -DTEST_PROGRAM $(srcdir)/dev.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_devname: $(srcdir)/devname.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_devname -DTEST_PROGRAM $(srcdir)/devname.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_devno: $(srcdir)/devno.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_devno -DTEST_PROGRAM $(srcdir)/devno.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_getsize: $(srcdir)/getsize.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_getsize -DTEST_PROGRAM $(srcdir)/getsize.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_probe: $(srcdir)/probe.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_probe -DTEST_PROGRAM $(srcdir)/probe.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_read: $(srcdir)/read.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_read -DTEST_PROGRAM $(srcdir)/read.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_resolve: $(srcdir)/resolve.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_resolve -DTEST_PROGRAM $(srcdir)/resolve.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_save: $(srcdir)/save.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_save -DTEST_PROGRAM $(srcdir)/save.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_tag: $(srcdir)/tag.c $(DEPLIBS_BLKID)
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_tag -DTEST_PROGRAM $(srcdir)/tag.c $(LIBS_BLKID) $(ALL_CFLAGS)

tst_types: tst_types.o blkid_types.h 
	$(E) "	LD $@"
	$(Q) $(CC) -o tst_types $(ALL_LDFLAGS) tst_types.o

../../misc/blkid.o: $(top_srcdir)/misc/blkid.c blkid.h
	$(E) "	CC $@"
	$(Q) $(CC) $(ALL_CFLAGS) -c $(top_srcdir)/misc/blkid.c \
		-o ../../misc/blkid.o

blkid: ../../misc/blkid.o libblkid.a $(DEPLIBUUID)
	$(E) "	LD $@"
	$(Q) $(CC) -o blkid ../../misc/blkid.o libblkid.a $(LIBUUID)

test_probe: test_probe.in Makefile
	$(E) "Creating test_probe..."
	$(E) "#!/bin/sh" > test_probe
	$(E) "SRCDIR=../../../lib/blkid" >> test_probe
	$(Q) cat $(srcdir)/test_probe.in >> test_probe
	$(Q) chmod +x test_probe

fullcheck check:: all tst_cache tst_dev tst_devname tst_devno \
 tst_getsize tst_probe tst_read tst_resolve tst_save tst_tag \
 test_probe tst_types
	./test_probe
	./tst_types

blkid.pc: $(srcdir)/blkid.pc.in $(top_builddir)/config.status
	$(E) "	CONFIG.STATUS $@"
	$(Q) cd $(top_builddir); CONFIG_FILES=lib/blkid/blkid.pc ./config.status

installdirs::
	$(E) "	MKINSTALLDIRS $(libdir) $(includedir)/blkid"
	$(Q) $(MKINSTALLDIRS) $(DESTDIR)$(libdir) \
		$(DESTDIR)$(includedir)/blkid $(DESTDIR)$(pkgconfigdir)

install:: all installdirs 
	$(E) "	INSTALL_DATA $(libdir)/libblkid.a"
	$(Q) $(INSTALL_DATA) libblkid.a $(DESTDIR)$(libdir)/libblkid.a
	-$(Q) $(RANLIB) $(DESTDIR)$(libdir)/libblkid.a
	$(Q) $(CHMOD) $(LIBMODE) $(DESTDIR)$(libdir)/libblkid.a
	$(Q) set -e; for i in $(HFILES_IN); do \
		echo "	INSTALL_DATA $(includedir)/blkid/$$i"; \
		$(INSTALL_DATA) $$i $(DESTDIR)$(includedir)/blkid/$$i; \
	done
	$(Q) for i in $(SMANPAGES); do \
		echo "	INSTALL_DATA $(man3dir)/$$i"; \
		$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$i; \
	done
	$(E) "	INSTALL_DATA $(pkgconfigdir)/blkid.pc"
	$(Q) $(INSTALL_DATA) blkid.pc $(DESTDIR)$(pkgconfigdir)/blkid.pc

uninstall::
	$(RM) -f $(DESTDIR)$(libdir)/libblkid.a \
		$(DESTDIR)$(pkgconfigdir)/blkid.pc
	$(RM) -rf $(DESTDIR)$(includedir)/blkid
	for i in $(SMANPAGES); do \
		$(RM) -f $(DESTDIR)$(man3dir)/$$i; \
	done

clean::
	$(RM) -f \#* *.s *.o *.orig *.a *~ *.bak tst_cache tst_dev tst_devname \
		tst_devno tst_getsize tst_probe tst_read tst_resolve tst_save \
		tst_tag tst_types tests/*.out tests/*.ok \
		tests/*.img results test_probe core profiled/* \
		blkid.h blkid_types.h ../libblkid.a ../libblkid_p.a \
		$(SMANPAGES) blkid blkid.pc
	@echo rmdir tests/tmp tests
	@(rmdir tests/tmp tests 2> /dev/null ; exit 0)

mostlyclean:: clean
distclean:: clean
	$(RM) -f .depend Makefile blkid.pc \
		$(srcdir)/TAGS $(srcdir)/Makefile.in.old

$(OBJS): subdirs $(HFILES_IN)

# +++ Dependency line eater +++
# 
# Makefile dependencies follow.  This must be the last section in
# the Makefile.in file
#
cache.o: $(srcdir)/cache.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
dev.o: $(srcdir)/dev.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
devname.o: $(srcdir)/devname.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
devno.o: $(srcdir)/devno.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
getsize.o: $(srcdir)/getsize.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
llseek.o: $(srcdir)/llseek.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
probe.o: $(srcdir)/probe.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h \
 $(srcdir)/probe.h
read.o: $(srcdir)/read.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
resolve.o: $(srcdir)/resolve.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
save.o: $(srcdir)/save.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
tag.o: $(srcdir)/tag.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/blkidP.h $(srcdir)/list.h
version.o: $(srcdir)/version.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(top_srcdir)/version.h
