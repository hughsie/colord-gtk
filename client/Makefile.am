INCLUDES =						\
	$(GLIB_CFLAGS)					\
	$(GTK3_CFLAGS)					\
	$(COLORD_CFLAGS)				\
	-I$(top_srcdir)					\
	-I$(top_srcdir)/libcolord-gtk			\
	-DG_LOG_DOMAIN=\"Cd\"				\
	-DCD_COMPILATION				\
	-DVERSION="\"$(VERSION)\""			\
	-DLOCALEDIR=\""$(localedir)"\"

COLORD_GTK_LIBS =					\
	$(top_builddir)/libcolord-gtk/libcolord-gtk.la

bin_PROGRAMS =						\
	cd-convert

cd_convert_SOURCES =					\
	cd-convert.c

cd_convert_LDADD =					\
	$(LCMS_LIBS)					\
	$(COLORD_LIBS)					\
	$(COLORD_GTK_LIBS)				\
	$(GTK3_LIBS)					\
	$(GLIB_LIBS)					\
	-lm

cd_convert_CFLAGS =					\
	$(WARNINGFLAGS_C)

-include $(top_srcdir)/git.mk
