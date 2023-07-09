## Process this file with automake to produce Makefile.in

SUBDIRS = intl sted2 po etc doc contrib

EXTRA_DIST = README.jp ChangeLog.old \
	intl/libgettext.h \
	intl/po2tbl.sed.in

YYMMDD=`date +%Y%m%d`

.PHONY: .version

.version:
	-rm $(srcdir)/sted2/version.h
	echo "#define VERSION_ID	\"$(YYMMDD)\"" > $(srcdir)/sted2/version.h
	autoconf

