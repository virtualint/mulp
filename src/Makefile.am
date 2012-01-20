## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	$(WX_CXXFLAGS) \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(LIBXML_CFLAGS)

AM_CFLAGS =\
	 -Wall \
	 -g \
	 $(WX_CPPFLAGS)

bin_PROGRAMS = mulp

mulp_SOURCES = \
	main.cc\
	SlackFrame.h\
	SlackFrame.cc \
	PluginButton.h \
	PluginButton.cc \
	Plugin.h \
	Plugin.cc \
	Parser.h \
	Parser.cc \
	Page.h \
	Page.cc \
	NodeInfo.h \
	NodeInfo.cc \
	Exception.h \
	AboutDialog.h \
	AboutDialog.cc \
	DialogPlugin.h \
	DialogPlugin.cc

mulp_LDFLAGS = 

mulp_LDADD = \
	 $(WX_LIBS) \
	 $(LIBXML_LIBS)
	 