#
# Standard e2fsprogs prologue....
#

srcdir = ../../debugfs
top_srcdir = ../..
VPATH = ../../debugfs
top_builddir = ..
my_dir = debugfs
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
AWK = gawk
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
LIBBLKID = -lblkid  $(LIBUUID)
LIBINTL = 
SYSLIBS = -lblkid 
DEPLIBSS = $(LIB)/libss.a
DEPLIBCOM_ERR = $(LIB)/libcom_err.a
DEPLIBUUID = 
DEPLIBSUPPORT = $(LIB)/libsupport.a
DEPLIBBLKID =   $(DEPLIBUUID)
TESTENV = LD_LIBRARY_PATH="$(LIB):$${LD_LIBRARY_PATH}" DYLD_LIBRARY_PATH="$(LIB):$${DYLD_LIBRARY_PATH}"

STATIC_LIBSS = $(LIB)/libss.a -ldl
STATIC_LIBCOM_ERR = $(LIB)/libcom_err.a -lpthread
STATIC_LIBE2P = $(LIB)/libe2p.a
STATIC_LIBEXT2FS = $(LIB)/libext2fs.a
STATIC_LIBUUID = -luuid 
STATIC_LIBSUPPORT = $(LIBINTL) $(LIBSUPPORT)
STATIC_LIBBLKID = -lblkid -luuid $(STATIC_LIBUUID)
DEPSTATIC_LIBSS = $(LIB)/libss.a
DEPSTATIC_LIBCOM_ERR = $(LIB)/libcom_err.a
DEPSTATIC_LIBUUID = 
DEPSTATIC_LIBSUPPORT = $(DEPLIBSUPPORT)
DEPSTATIC_LIBBLKID =  $(DEPSTATIC_LIBUUID)

PROFILED_LIBSS = $(LIB)/libss.a -ldl
PROFILED_LIBCOM_ERR = $(LIB)/libcom_err.a -lpthread
PROFILED_LIBE2P = $(LIB)/libe2p.a
PROFILED_LIBEXT2FS = $(LIB)/libext2fs.a
PROFILED_LIBUUID = -luuid 
PROFILED_LIBSUPPORT = $(LIBINTL) $(LIB)/libsupport.a
PROFILED_LIBBLKID = -lblkid $(PROFILED_LIBUUID)
DEPPROFILED_LIBSS = $(LIB)/libss.a
DEPPROFILED_LIBCOM_ERR = $(LIB)/libcom_err.a
DEPPROFILED_LIBUUID = -luuid
DEPPROFILED_LIBSUPPORT = $(PROFILED_LIBSUPPORT)
DEPPROFILED_LIBBLKID = -lblkid $(DEPPROFILED_LIBUUID)

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

PROGS=		debugfs
MANPAGES=	debugfs.8

MK_CMDS=	_SS_DIR_OVERRIDE=$(srcdir)/../lib/ss ../lib/ss/mk_cmds

DEBUG_OBJS= debug_cmds.o debugfs.o util.o ncheck.o icheck.o ls.o \
	lsdel.o dump.o set_fields.o logdump.o htree.o unused.o e2freefrag.o \
	filefrag.o extent_cmds.o extent_inode.o zap.o create_inode.o \
	quota.o xattrs.o journal.o revoke.o recovery.o do_journal.o

RO_DEBUG_OBJS= ro_debug_cmds.o ro_debugfs.o util.o ncheck.o icheck.o ls.o \
	lsdel.o logdump.o htree.o e2freefrag.o filefrag.o extent_cmds.o \
	extent_inode.o quota.o xattrs.o

SRCS= debug_cmds.c $(srcdir)/debugfs.c $(srcdir)/util.c $(srcdir)/ls.c \
	$(srcdir)/ncheck.c $(srcdir)/icheck.c $(srcdir)/lsdel.c \
	$(srcdir)/dump.c $(srcdir)/set_fields.c ${srcdir}/logdump.c \
	$(srcdir)/htree.c $(srcdir)/unused.c ${srcdir}/../misc/e2freefrag.c \
	$(srcdir)/filefrag.c $(srcdir)/extent_inode.c $(srcdir)/zap.c \
	$(srcdir)/../misc/create_inode.c $(srcdir)/xattrs.c $(srcdir)/quota.c \
	$(srcdir)/journal.c $(srcdir)/../e2fsck/revoke.c \
	$(srcdir)/../e2fsck/recovery.c $(srcdir)/do_journal.c

LIBS= $(LIBSUPPORT) $(LIBEXT2FS) $(LIBE2P) $(LIBSS) $(LIBCOM_ERR) $(LIBBLKID) \
	$(LIBUUID) $(LIBMAGIC) $(SYSLIBS)
DEPLIBS= $(DEPLIBSUPPORT) $(LIBEXT2FS) $(LIBE2P) $(DEPLIBSS) $(DEPLIBCOM_ERR) \
	$(DEPLIBBLKID) $(DEPLIBUUID)

STATIC_LIBS= $(STATIC_LIBSUPPORT) $(STATIC_LIBEXT2FS) $(STATIC_LIBSS) \
	$(STATIC_LIBCOM_ERR) $(STATIC_LIBBLKID) $(STATIC_LIBUUID) \
	$(STATIC_LIBE2P) $(LIBMAGIC) $(SYSLIBS)
STATIC_DEPLIBS= $(STATIC_LIBEXT2FS) $(DEPSTATIC_LIBSS) \
		$(DEPSTATIC_LIBCOM_ERR) $(DEPSTATIC_LIBUUID) \
		$(DEPSTATIC_LIBE2P)

# This nastyness is needed because of jfs_user.h hackery; when we finally
# clean up this mess, we should be able to drop it
LOCAL_CFLAGS = -I$(srcdir)/../e2fsck -DDEBUGFS
DEPEND_CFLAGS = -I$(srcdir)

.c.o:
	$(E) "	CC $<"
	$(Q) $(CC) -c $(ALL_CFLAGS) $< -o $@
	$(Q) $(CHECK_CMD) $(ALL_CFLAGS) $<
	$(Q) $(CPPCHECK_CMD) $(CPPFLAGS) $<

all:: $(PROGS) $(MANPAGES)

debugfs: $(DEBUG_OBJS) $(DEPLIBS)
	$(E) "	LD $@"
	$(Q) $(CC) $(ALL_LDFLAGS) -o debugfs $(DEBUG_OBJS) $(LIBS)

debugfs.static: $(DEBUG_OBJS) $(STATIC_DEPLIBS)
	$(E) "	LD $@"
	$(Q) $(CC) $(LDFLAGS_STATIC) -o debugfs.static $(DEBUG_OBJS) \
		$(STATIC_LIBS) $(READLINE_LIB)

debugfs.static-libs: $(DEBUG_OBJS) $(STATIC_DEPLIBS)
	$(E) "	LD $@"
	$(Q) $(CC) -o debugfs.static-libs $(DEBUG_OBJS) \
		$(STATIC_LIBS) $(READLINE_LIB)

rdebugfs: $(RO_DEBUG_OBJS) $(DEPLIBS)
	$(E) "	LD $@"
	$(Q) $(CC) $(ALL_LDFLAGS) -o rdebugfs $(RO_DEBUG_OBJS) $(LIBS)

debug_cmds.c debug_cmds.h: debug_cmds.ct
	$(E) "	MK_CMDS $@"
	$(Q) $(MK_CMDS) $(srcdir)/debug_cmds.ct

extent_cmds.c extent_cmds.h: extent_cmds.ct
	$(E) "	MK_CMDS $@"
	$(Q) $(MK_CMDS) $(srcdir)/extent_cmds.ct

ro_debug_cmds.c ro_debug_cmds.h: ro_debug_cmds.ct
	$(E) "	MK_CMDS $@"
	$(Q) $(MK_CMDS) $(srcdir)/ro_debug_cmds.ct

ro_debugfs.o: debugfs.c
	$(E) "	CC $@"
	$(Q) $(CC) -c $(ALL_CFLAGS) $< -DREAD_ONLY -o $@

e2freefrag.o: $(srcdir)/../misc/e2freefrag.c
	$(E) "	CC $@"
	$(Q) $(CC) -c $(ALL_CFLAGS) -I$(srcdir) $< -o $@

recovery.o: $(srcdir)/../e2fsck/recovery.c
	$(E) "	CC $@"
	$(Q) $(CC) -c $(ALL_CFLAGS) -I$(srcdir) \
		$(srcdir)/../e2fsck/recovery.c -o $@

revoke.o: $(srcdir)/../e2fsck/revoke.c
	$(E) "	CC $@"
	$(Q) $(CC) -c $(ALL_CFLAGS) -I$(srcdir) \
		$(srcdir)/../e2fsck/revoke.c -o $@

create_inode.o: $(srcdir)/../misc/create_inode.c
	$(E) "	CC $@"
	$(Q) $(CC) -c $(ALL_CFLAGS) -I$(srcdir) \
		 $(srcdir)/../misc/create_inode.c -o $@

debugfs.8: $(DEP_SUBSTITUTE) $(srcdir)/debugfs.8.in
	$(E) "	SUBST $@"
	$(Q) $(SUBSTITUTE_UPTIME) $(srcdir)/debugfs.8.in debugfs.8

installdirs:
	$(E) "	MKINSTALLDIRS $(root_sbindir) $(man8dir)"
	$(Q) $(MKINSTALLDIRS) $(DESTDIR)$(root_sbindir) \
		$(DESTDIR)$(man8dir)

install: $(PROGS) $(MANPAGES) installdirs
	$(Q) for i in $(PROGS); do \
		echo "	INSTALL $(root_sbindir)/$$i"; \
		$(INSTALL_PROGRAM) $$i $(DESTDIR)$(root_sbindir)/$$i; \
	done
	$(Q) for i in $(MANPAGES); do \
		for j in $(COMPRESS_EXT); do \
			$(RM) -f $(DESTDIR)$(man8dir)/$$i.$$j; \
		done; \
		echo "	INSTALL_DATA $(man8dir)/$$i"; \
		$(INSTALL_DATA) $$i $(DESTDIR)$(man8dir)/$$i; \
	done

install-strip: install
	$(Q) for i in $(PROGS); do \
		echo "	STRIP $(root_sbindir)/$$i"; \
		$(STRIP) $(DESTDIR)$(root_sbindir)/$$i; \
	done

uninstall:
	for i in $(PROGS); do \
		$(RM) -f $(DESTDIR)$(root_sbindir)/$$i; \
	done
	for i in $(MANPAGES); do \
		$(RM) -f $(DESTDIR)$(man8dir)/$$i; \
	done

clean::
	$(RM) -f $(PROGS) debugfs.8 \#* *.s *.o *.a *~ debug_cmds.c \
		extent_cmds.c ro_debug_cmds.c core rdebugfs debugfs.static \
		debugfs.static-libs tst_set_fields

mostlyclean: clean
distclean: clean
	$(RM) -f debug_cmds.c .depend Makefile $(srcdir)/TAGS \
		$(srcdir)/Makefile.in.old $(srcdir)/recovery.c \
		$(srcdir)/revoke.c

tst_set_fields: set_fields.c util.c
	$(E) "  LD $@"
	$(Q) $(CC) $(ALL_CFLAGS) $(ALL_LDFLAGS) $(SYSLIBS) -DUNITTEST \
		-o tst_set_fields $(srcdir)/set_fields.c $(srcdir)/util.c $(LIBS)

fullcheck check:: tst_set_fields
	$(TESTENV) ./tst_set_fields

# +++ Dependency line eater +++
# 
# Makefile dependencies follow.  This must be the last section in
# the Makefile.in file
#
debug_cmds.o: debug_cmds.c $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h
debugfs.o: $(srcdir)/debugfs.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h $(top_srcdir)/version.h \
 $(srcdir)/../e2fsck/jfs_user.h $(top_srcdir)/lib/ext2fs/kernel-jbd.h \
 $(top_srcdir)/lib/ext2fs/jfs_compat.h $(top_srcdir)/lib/ext2fs/kernel-list.h \
 $(top_srcdir)/lib/support/plausible.h
util.o: $(srcdir)/util.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(srcdir)/debugfs.h $(top_srcdir)/lib/ext2fs/ext2_fs.h \
 $(top_builddir)/lib/ext2fs/ext2_types.h $(top_srcdir)/lib/ext2fs/ext2fs.h \
 $(top_srcdir)/lib/ext2fs/ext3_extents.h $(top_srcdir)/lib/ext2fs/ext2_io.h \
 $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
ls.o: $(srcdir)/ls.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
ncheck.o: $(srcdir)/ncheck.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
icheck.o: $(srcdir)/icheck.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
lsdel.o: $(srcdir)/lsdel.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
dump.o: $(srcdir)/dump.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
set_fields.o: $(srcdir)/set_fields.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
logdump.o: $(srcdir)/logdump.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h $(srcdir)/../e2fsck/jfs_user.h \
 $(top_srcdir)/lib/ext2fs/kernel-jbd.h $(top_srcdir)/lib/ext2fs/jfs_compat.h \
 $(top_srcdir)/lib/ext2fs/kernel-list.h
htree.o: $(srcdir)/htree.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
unused.o: $(srcdir)/unused.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
e2freefrag.o: $(srcdir)/../misc/e2freefrag.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(top_srcdir)/lib/ext2fs/ext2_fs.h \
 $(top_builddir)/lib/ext2fs/ext2_types.h $(top_srcdir)/lib/ext2fs/ext2fs.h \
 $(top_srcdir)/lib/ext2fs/ext3_extents.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/e2freefrag.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(srcdir)/../misc/create_inode.h \
 $(top_srcdir)/lib/e2p/e2p.h $(top_srcdir)/lib/support/quotaio.h \
 $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
filefrag.o: $(srcdir)/filefrag.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
extent_inode.o: $(srcdir)/extent_inode.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
zap.o: $(srcdir)/zap.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
create_inode.o: $(srcdir)/../misc/create_inode.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(top_srcdir)/lib/ext2fs/ext2fs.h \
 $(top_builddir)/lib/ext2fs/ext2_types.h $(top_srcdir)/lib/ext2fs/ext2_fs.h \
 $(top_srcdir)/lib/ext2fs/ext3_extents.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(top_srcdir)/lib/ext2fs/fiemap.h $(srcdir)/../misc/create_inode.h \
 $(top_srcdir)/lib/e2p/e2p.h $(top_srcdir)/lib/support/nls-enable.h
xattrs.o: $(srcdir)/xattrs.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(top_srcdir)/lib/support/cstring.h \
 $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
quota.o: $(srcdir)/quota.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h
journal.o: $(srcdir)/journal.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/journal.h \
 $(srcdir)/../e2fsck/jfs_user.h $(top_srcdir)/lib/ext2fs/ext2_fs.h \
 $(top_builddir)/lib/ext2fs/ext2_types.h $(top_srcdir)/lib/ext2fs/ext2fs.h \
 $(top_srcdir)/lib/ext2fs/ext3_extents.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(top_srcdir)/lib/ext2fs/kernel-jbd.h $(top_srcdir)/lib/ext2fs/jfs_compat.h \
 $(top_srcdir)/lib/ext2fs/kernel-list.h
revoke.o: $(srcdir)/../e2fsck/revoke.c $(srcdir)/../e2fsck/jfs_user.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/et/com_err.h $(top_srcdir)/lib/ext2fs/ext2_io.h \
 $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(top_srcdir)/lib/ext2fs/kernel-jbd.h $(top_srcdir)/lib/ext2fs/jfs_compat.h \
 $(top_srcdir)/lib/ext2fs/kernel-list.h
recovery.o: $(srcdir)/../e2fsck/recovery.c $(srcdir)/../e2fsck/jfs_user.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/et/com_err.h $(top_srcdir)/lib/ext2fs/ext2_io.h \
 $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(top_srcdir)/lib/ext2fs/kernel-jbd.h $(top_srcdir)/lib/ext2fs/jfs_compat.h \
 $(top_srcdir)/lib/ext2fs/kernel-list.h
do_journal.o: $(srcdir)/do_journal.c $(top_builddir)/lib/config.h \
 $(top_builddir)/lib/dirpaths.h $(srcdir)/debugfs.h $(top_srcdir)/lib/ss/ss.h \
 $(top_builddir)/lib/ss/ss_err.h $(top_srcdir)/lib/et/com_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_fs.h $(top_builddir)/lib/ext2fs/ext2_types.h \
 $(top_srcdir)/lib/ext2fs/ext2fs.h $(top_srcdir)/lib/ext2fs/ext3_extents.h \
 $(top_srcdir)/lib/ext2fs/ext2_io.h $(top_builddir)/lib/ext2fs/ext2_err.h \
 $(top_srcdir)/lib/ext2fs/ext2_ext_attr.h $(top_srcdir)/lib/ext2fs/bitops.h \
 $(srcdir)/../misc/create_inode.h $(top_srcdir)/lib/e2p/e2p.h \
 $(top_srcdir)/lib/support/quotaio.h $(top_srcdir)/lib/support/dqblk_v2.h \
 $(top_srcdir)/lib/support/quotaio_tree.h \
 $(top_srcdir)/lib/ext2fs/kernel-jbd.h $(top_srcdir)/lib/ext2fs/jfs_compat.h \
 $(top_srcdir)/lib/ext2fs/kernel-list.h $(srcdir)/journal.h \
 $(srcdir)/../e2fsck/jfs_user.h
