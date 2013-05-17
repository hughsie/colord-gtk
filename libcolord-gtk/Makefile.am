if HAVE_INTROSPECTION
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS =	--add-include-path=$(srcdir)		\
				--add-include-path=$(top_builddir)/libcolord-gtk
INTROSPECTION_COMPILER_ARGS =	--includedir=$(srcdir)			\
				--includedir=$(top_srcdir)/libcolord-gtk	\
				--includedir=$(top_builddir)/libcolord-gtk
endif

AM_CPPFLAGS = \
	$(GLIB_CFLAGS)						\
	$(COLORD_CFLAGS)					\
	-I$(top_srcdir)						\
	-I$(top_srcdir)/libcolord-gtk				\
	-DCD_COMPILATION					\
	-DG_LOG_DOMAIN=\"libcolord-gtk\"			\
	-DTESTDATADIR=\""$(top_srcdir)/data/tests"\"		\
	-DPACKAGE_DATA_DIR=\""$(datadir)"\"

lib_LTLIBRARIES =						\
	libcolord-gtk.la

libcolord_includedir = $(includedir)/colord-1
libcolord_include_HEADERS =					\
	colord-gtk.h

libcolordgtkbase_includedir = $(libcolord_includedir)/colord-gtk
libcolordgtkbase_include_HEADERS =				\
	cd-version.h						\
	cd-sample-widget.h					\
	cd-sample-window.h					\
	cd-window.h						\
	cd-window-sync.h

libcolord_gtk_la_SOURCES =					\
	cd-sample-widget.c					\
	cd-sample-window.c					\
	cd-window.c						\
	cd-window-sync.c

libcolord_gtk_la_LIBADD =					\
	$(COLORD_LIBS)						\
	$(GTK3_LIBS)						\
	$(GLIB_LIBS)

libcolord_gtk_la_CPPFLAGS =					\
	$(AM_CPPFLAGS)						\
	$(GTK3_CFLAGS)

libcolord_gtk_la_LDFLAGS =					\
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)	\
	-export-dynamic						\
	-no-undefined						\
	-export-symbols-regex '^cd_.*'

libcolord_gtk_la_CFLAGS =					\
	$(WARNINGFLAGS_C)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = colord-gtk.pc

if HAVE_GTK2
pkgconfig_DATA += colord-gtk2.pc
lib_LTLIBRARIES +=						\
	libcolord-gtk2.la

libcolord_gtk2_la_SOURCES =					\
	cd-window.c						\
	cd-window-sync.c

libcolord_gtk2_la_LIBADD =					\
	$(COLORD_LIBS)						\
	$(GTK2_LIBS)						\
	$(GLIB_LIBS)

libcolord_gtk2_la_CPPFLAGS =					\
	$(AM_CPPFLAGS)						\
	$(GTK2_CFLAGS)

libcolord_gtk2_la_LDFLAGS =					\
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)	\
	-export-dynamic						\
	-no-undefined						\
	-export-symbols-regex '^cd_.*'

libcolord_gtk2_la_CFLAGS =					\
	$(WARNINGFLAGS_C)
endif

check_PROGRAMS =						\
	cd-self-test

cd_self_test_SOURCES =						\
	cd-self-test.c

cd_self_test_CPPFLAGS =						\
	$(AM_CPPFLAGS)						\
	$(GTK3_CFLAGS)

cd_self_test_LDADD =						\
	$(COLORD_LIBS)						\
	$(GLIB_LIBS)						\
	$(GTK3_LIBS)						\
	libcolord-gtk.la

cd_self_test_CFLAGS = $(WARNINGFLAGS_C)

TESTS = cd-self-test

EXTRA_DIST =							\
	colord-gtk.pc.in					\
	colord-gtk2.pc.in

MAINTAINERCLEANFILES =						\
	$(noinst_LIBRARIES)

CLEANFILES = $(BUILT_SOURCES)

if HAVE_INTROSPECTION
introspection_sources =						\
	$(libcolord_gtk_la_SOURCES)				\
	$(libcolordgtkbase_include_HEADERS)

ColordGtk-1.0.gir: libcolord-gtk.la
ColordGtk_1_0_gir_INCLUDES = GObject-2.0 Gio-2.0 Gtk-3.0 Colord-1.0
ColordGtk_1_0_gir_CFLAGS = $(AM_CPPFLAGS)
ColordGtk_1_0_gir_SCANNERFLAGS = --identifier-prefix=Cd \
				--symbol-prefix=cd \
				--warn-all \
				--add-include-path=$(srcdir) \
				--add-include-path=$(top_srcdir)/libcolord \
				--c-include="colord-gtk.h"
ColordGtk_1_0_gir_EXPORT_PACKAGES = colord-gtk
ColordGtk_1_0_gir_LIBS = libcolord-gtk.la
ColordGtk_1_0_gir_FILES = $(introspection_sources)
INTROSPECTION_GIRS += ColordGtk-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(gir_DATA) $(typelib_DATA)

if HAVE_VAPIGEN
colord-gtk.vapi: ColordGtk-1.0.gir
	$(MAKE) $(AM_MAKEFLAGS) ColordGtk-1.0.gir
	$(AM_V_GEN)$(VAPIGEN) $(VAPIGENFLAGS)			\
		--library colord-gtk				\
		--vapidir $(top_builddir)/libcolord		\
		--pkg gio-2.0					\
		--pkg gtk+-3.0					\
		--pkg colord					\
		ColordGtk-1.0.gir
	touch $@
vapidir = $(datadir)/vala/vapi
dist_vapi_DATA =						\
	colord-gtk.vapi
CLEANFILES += $(dist_vapi_DATA)
endif

endif

clean-local:
	rm -f *~

-include $(top_srcdir)/git.mk
