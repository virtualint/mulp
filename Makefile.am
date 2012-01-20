## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po \
	setting  plugins\
	images

mulpdocdir = ${prefix}/doc/mulp
mulpdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

mulpsettingdir = /etc/mulp
mulpsetting_DATA = \
	setting/mulp.xml \
	setting/ubuntu.xml
	

INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(mulpdoc_DATA) \
	$(INTLTOOL_FILES) \
	$(mulpsetting_DATA)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(mulpdocdir)
	-rm -r $(mulpsettingdir)
