# Makefile for the UUID library
#

srcdir = ../../../lib/uuid
top_srcdir = ../../..
VPATH = ../../../lib/uuid
top_builddir = ../..
my_dir = lib/uuid
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
LIBUUID = $(LIB)/libuuid.a 
LIBMAGIC = -ldl
LIBFUSE = 
LIBSUPPORT = $(LIBINTL) $(LIB)/libsupport.a
LIBBLKID = $(LIB)/libblkid.a  $(LIBUUID)
LIBINTL = 
SYSLIBS = 
DEPLIBSS = $(LIB)/libss.a
DEPLIBCOM_ERR = $(LIB)/libcom_err.a
DEPLIBUUID = $(LIB)/libuuid.a
DEPLIBSUPPORT = $(LIB)/libsupport.a
DEPLIBBLKID = $(LIB)/libblkid.a  $(DEPLIBUUID)
TESTENV = LD_LIBRARY_PATH="$(LIB):$${LD_LIBRARY_PATH}" DYLD_LIBRARY_PATH="$(LIB):$${DYLD_LIBRARY_PATH}"

STATIC_LIBSS = $(LIB)/libss.a -ldl
STATIC_LIBCOM_ERR = $(LIB)/libcom_err.a -lpthread
STATIC_LIBE2P = $(LIB)/libe2p.a
STATIC_LIBEXT2FS = $(LIB)/libext2fs.a
STATIC_LIBUUID = $(LIB)/libuuid.a 
STATIC_LIBSUPPORT = $(LIBINTL) $(LIBSUPPORT)
STATIC_LIBBLKID = $(LIB)/libblkid.a $(STATIC_LIBUUID)
DEPSTATIC_LIBSS = $(LIB)/libss.a
DEPSTATIC_LIBCOM_ERR = $(LIB)/libcom_err.a
DEPSTATIC_LIBUUID = $(LIB)/libuuid.a
DEPSTATIC_LIBSUPPORT = $(DEPLIBSUPPORT)
DEPSTATIC_LIBBLKID = $(LIB)/libblkid.a $(DEPSTATIC_LIBUUID)

PROFILED_LIBSS = $(LIB)/libss.a -ldl
PROFILED_LIBCOM_ERR = $(LIB)/libcom_err.a -lpthread
PROFILED_LIBE2P = $(LIB)/libe2p.a
PROFILED_LIBEXT2FS = $(LIB)/libext2fs.a
PROFILED_LIBUUID = $(LIB)/libuuid.a 
PROFILED_LIBSUPPORT = $(LIBINTL) $(LIB)/libsupport.a
PROFILED_LIBBLKID = $(LIB)/libblkid.a $(PROFILED_LIBUUID)
DEPPROFILED_LIBSS = $(LIB)/libss.a
DEPPROFILED_LIBCOM_ERR = $(LIB)/libcom_err.a
DEPPROFILED_LIBUUID = $(LIB)/libuuid.a
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

SMANPAGES=	uuid.3 uuid_clear.3 uuid_compare.3 uuid_copy.3 \
		uuid_generate.3 uuid_is_null.3 uuid_parse.3 \
		uuid_time.3 uuid_unparse.3

OBJS=		clear.o \
		compare.o \
		copy.o \
		gen_uuid.o \
		isnull.o \
		pack.o \
		parse.o \
		unpack.o \
		unparse.o \
		uuid_time.o

SRCS=		$(srcdir)/clear.c \
		$(srcdir)/compare.c \
		$(srcdir)/copy.c \
		$(srcdir)/gen_uuid.c \
		$(srcdir)/isnull.c \
		$(srcdir)/pack.c \
		$(srcdir)/parse.c \
		$(srcdir)/unpack.c \
		$(srcdir)/unparse.c \
		$(srcdir)/uuid_time.c

LIBRARY= libuuid
LIBDIR= uuid

ELF_VERSION = 1.2
ELF_SO_VERSION = 1
ELF_IMAGE = libuuid
ELF_MYDIR = uuid
ELF_INSTALL_DIR = $(root_libdir)
ELF_OTHER_LIBS = 

BSDLIB_VERSION = 1.1
BSDLIB_IMAGE = libuuid
BSDLIB_MYDIR = uuid
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

.c.o:
	$(E) "	CC $<"
	$(Q) $(CC) $(ALL_CFLAGS_STLIB) -c $< -o $@
	$(Q) $(CHECK_CMD) $(ALL_CFLAGS) $<
	$(Q) $(CPPCHECK_CMD) $(CPPFLAGS) $<
#	$(Q) $(CC) $(ALL_CFLAGS_STLIB) -g -pg -o profiled/$*.o -c $<
#	$(Q) $(CC) $(ALL_CFLAGS_SHLIB) -fPIC -shared -o elfshared/$*.o -c $<
#	$(Q) $(CC) $(ALL_CFLAGS_SHLIB) $(BSDLIB_PIC_FLAG) -o pic/$*.o -c $<

all:: tst_uuid uuid_time $(SMANPAGES) uuid.pc

uuid.h: $(srcdir)/uuid.h.in
	$(E) "	CP $@"
	$(Q) cp $(srcdir)/uuid.h.in uuid.h

$(top_builddir)/lib/uuid/uuid_types.h: $(srcdir)/uuid_types.h.in $(top_builddir)/config.status
	cd $(top_builddir); CONFIG_FILES=$(my_dir)/uuid_types.h ./config.status

tst_uuid.o: $(srcdir)/tst_uuid.c uuid.h
	$(E) "	CC $@"
	$(Q) $(CC) $(ALL_CFLAGS) -c $(srcdir)/tst_uuid.c -o tst_uuid.o

tst_uuid: tst_uuid.o $(DEPSTATIC_LIBUUID)
	$(E) "	LD $@"
	$(Q) $(CC) $(ALL_LDFLAGS) -o tst_uuid tst_uuid.o $(STATIC_LIBUUID)

uuid_time: $(srcdir)/uuid_time.c $(DEPLIBUUID)
	$(E) "	LD $@"
	$(Q) $(CC) $(ALL_CFLAGS) $(LDFLAGS) -DDEBUG -o uuid_time \
		$(srcdir)/uuid_time.c $(LIBUUID)

uuid.3: $(DEP_SUBSTITUTE) $(srcdir)/uuid.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/uuid.3.in uuid.3

uuid_clear.3: $(DEP_SUBSTITUTE) $(srcdir)/uuid_clear.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/uuid_clear.3.in uuid_clear.3

uuid_compare.3: $(DEP_SUBSTITUTE) $(srcdir)/uuid_compare.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/uuid_compare.3.in uuid_compare.3

uuid_copy.3: $(DEP_SUBSTITUTE) $(srcdir)/uuid_copy.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/uuid_copy.3.in uuid_copy.3

uuid_generate.3: $(DEP_SUBSTITUTE) $(srcdir)/uuid_generate.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/uuid_generate.3.in uuid_generate.3

uuid_is_null.3: $(DEP_SUBSTITUTE) $(srcdir)/uuid_is_null.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/uuid_is_null.3.in uuid_is_null.3

uuid_parse.3: $(DEP_SUBSTITUTE) $(srcdir)/uuid_parse.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/uuid_parse.3.in uuid_parse.3

uuid_time.3: $(DEP_SUBSTITUTE) $(srcdir)/uuid_time.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/uuid_time.3.in uuid_time.3

uuid_unparse.3: $(DEP_SUBSTITUTE) $(srcdir)/uuid_unparse.3.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/uuid_unparse.3.in uuid_unparse.3

uuid.pc: $(srcdir)/uuid.pc.in $(top_builddir)/config.status
	$(E) "	CONFIG.STATUS $@"
	$(Q) cd $(top_builddir); CONFIG_FILES=lib/uuid/uuid.pc ./config.status

installdirs::
	$(E) "	MKINSTALLDIRS $(libdir) $(includedir)/uuid $(man3dir)"
	$(Q) $(MKINSTALLDIRS) $(DESTDIR)$(libdir)  \
		$(DESTDIR)$(includedir)/uuid $(DESTDIR)$(man3dir) \
		$(DESTDIR)$(pkgconfigdir)

install:: all installdirs 
	$(E) "	INSTALL_DATA $(libdir)/libuuid.a"
	$(Q) $(INSTALL_DATA) libuuid.a $(DESTDIR)$(libdir)/libuuid.a
	-$(Q) $(RANLIB) $(DESTDIR)$(libdir)/libuuid.a
	$(Q) $(CHMOD) $(LIBMODE) $(DESTDIR)$(libdir)/libuuid.a
	$(E) "	INSTALL_DATA $(includedir)/uuid/uuid.h"
	$(Q) $(INSTALL_DATA) uuid.h $(DESTDIR)$(includedir)/uuid/uuid.h
	$(Q) for i in $(SMANPAGES); do \
		$(RM) -f $(DESTDIR)$(man3dir)/$$i.gz; \
		echo "	INSTALL_DATA $(man3dir)/$$i"; \
		$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$i; \
	done
	$(Q) $(RM) -f $(DESTDIR)$(man3dir)/uuid_generate_random.3.gz \
		$(DESTDIR)$(man3dir)/uuid_generate_time.3.gz
	$(E) "	LINK $(man3dir)/uuid_generate_random.3"
	$(Q) (cd $(DESTDIR)$(man3dir); \
	    $(LN) $(LINK_INSTALL_FLAGS) uuid_generate.3 uuid_generate_random.3)
	$(E) "	LINK $(man3dir)/uuid_generate_time.3"
	$(Q) (cd $(DESTDIR)$(man3dir); \
	    $(LN) $(LINK_INSTALL_FLAGS) uuid_generate.3 uuid_generate_time.3)
	$(E) "	INSTALL_DATA $(pkgconfigdir)/uuid.pc"
	$(Q) $(INSTALL_DATA) uuid.pc $(DESTDIR)$(pkgconfigdir)/uuid.pc

uninstall::
	$(RM) -f $(DESTDIR)$(libdir)/libuuid.a \
		$(DESTDIR)$(pkgconfigdir)/uuid.pc
	for i in $(SMANPAGES); do \
		$(RM) -f $(DESTDIR)$(man3dir)/$$i; \
	done
	$(RM) -f $(DESTDIR)$(man3dir)/uuid_generate_random.3 $(DESTDIR)$(man3dir)/uuid_generate_time.3

clean::
	$(RM) -f \#* *.s *.o *.a *~ *.bak core profiled/* uuid.h \
		../libuuid.a ../libuuid_p.a tst_uuid uuid_time \
		uuid.pc uuid_types.h $(SMANPAGES)

fullcheck check:: tst_uuid
	LD_LIBRARY_PATH=$(LIB) DYLD_LIBRARY_PATH=$(LIB) ./tst_uuid

mostlyclean:: clean
distclean:: clean
	$(RM) -f .depend Makefile uuid.pc \
		$(srcdir)/TAGS $(srcdir)/Makefile.in.old

#
# Hack to parallel makes recognize dependencies correctly.
#
../../lib/libuuid.a: libuuid.a
../../lib/libuuid.so: image
../../lib/libuuid.dylib: image

$(OBJS): subdirs uuid.h

# +++ Dependency line eater +++
# 
# Makefile dependencies follow.  This must be the last section in
# the Makefile.in file
#
clear.o: $(srcdir)/clear.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h
compare.o: $(srcdir)/compare.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h
copy.o: $(srcdir)/copy.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h
gen_uuid.o: $(srcdir)/gen_uuid.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h $(srcdir)/uuidd.h
isnull.o: $(srcdir)/isnull.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h
pack.o: $(srcdir)/pack.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h
parse.o: $(srcdir)/parse.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h
unpack.o: $(srcdir)/unpack.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h
unparse.o: $(srcdir)/unparse.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h
uuid_time.o: $(srcdir)/uuid_time.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/uuidP.h
