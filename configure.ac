# Copyright (C) 2012 Richard Hughes <richard@hughsie.com>
AC_PREREQ(2.63)

m4_define([cd_major_version], [0])
m4_define([cd_minor_version], [1])
m4_define([cd_micro_version], [26])
m4_define([cd_version],
          [cd_major_version.cd_minor_version.cd_micro_version])

AC_INIT([colord-gtk],[cd_version],[http://hughsie.com])
AC_CONFIG_SRCDIR(libcolord-gtk)
AM_INIT_AUTOMAKE([1.9 no-dist-gzip dist-xz tar-ustar])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_LIBTOOL

GOBJECT_INTROSPECTION_CHECK([0.9.8])

# set up gtk-doc
GTK_DOC_CHECK(1.9)

# use this in cd-version.h
CD_GTK_MAJOR_VERSION=cd_major_version
CD_GTK_MINOR_VERSION=cd_minor_version
CD_GTK_MICRO_VERSION=cd_micro_version
AC_SUBST(VERSION)
AC_SUBST(CD_GTK_MAJOR_VERSION)
AC_SUBST(CD_GTK_MINOR_VERSION)
AC_SUBST(CD_GTK_MICRO_VERSION)

# libtool versioning - this applies to libcolord-gtk
#
# See http://sources.redhat.com/autobook/autobook/autobook_91.html#SEC91 for details
#
# increment;
# CURRENT	If the API or ABI interface has changed (reset REVISION to 0)
# REVISION	If the API and ABI remains the same, but bugs are fixed.
# AGE		Don't use.
LT_CURRENT=1
LT_REVISION=3
LT_AGE=0
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

# enable nice build output on automake1.11
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AS_ALL_LINGUAS
AC_PROG_CC
AC_PROG_INSTALL
LT_INIT
AM_PROG_CC_C_O
IT_PROG_INTLTOOL([0.35.0])
AC_PATH_PROG(XSLTPROC, xsltproc)

dnl ---------------------------------------------------------------------------
dnl - Use strict options (default enabled for devs, disabled in releases)
dnl ---------------------------------------------------------------------------
if test -d ".git"; then
	default_strict=yes
else
	default_strict=no
fi

AC_ARG_ENABLE(strict, AS_HELP_STRING([--enable-strict],
				     [Enable strict compilation options]),
				     enable_strict=$enableval,
				     enable_strict=$default_strict)
if test x$enable_strict != xno; then
	CPPFLAGS="$CPPFLAGS -DG_DISABLE_SINGLE_INCLUDES -DGTK_DISABLE_SINGLE_INCLUDES"
	CPPFLAGS="$CPPFLAGS -DG_DISABLE_DEPRECATED"
	CPPFLAGS="$CPPFLAGS -DGSEAL_ENABLE"
fi

dnl ---------------------------------------------------------------------------
dnl - Extra verbose warning switches
dnl ---------------------------------------------------------------------------

if test "$GCC" = "yes"; then
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wall"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wcast-align -Wno-uninitialized"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wmissing-declarations"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wpointer-arith"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wcast-align"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wwrite-strings"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Winit-self"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wreturn-type"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wformat-nonliteral"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wformat-security"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wmissing-include-dirs"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wmissing-format-attribute"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wclobbered"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wempty-body"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wignored-qualifiers"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wsign-compare"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wtype-limits"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wuninitialized"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Waggregate-return"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wdeclaration-after-statement"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wshadow"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wno-strict-aliasing"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Winline"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Wmissing-parameter-type"
	WARNINGFLAGS_C="$WARNINGFLAGS_C -Woverride-init"
else
	WARNINGFLAGS_C=""
fi
AC_SUBST(WARNINGFLAGS_C)

dnl ---------------------------------------------------------------------------
dnl - gettext stuff
dnl ---------------------------------------------------------------------------
AM_GNU_GETTEXT_VERSION([0.17])
AM_GNU_GETTEXT([external])

GETTEXT_PACKAGE=AC_PACKAGE_NAME
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE(GETTEXT_PACKAGE, "AC_PACKAGE_NAME", [foo])

GLIB_GSETTINGS

dnl ---------------------------------------------------------------------------
dnl - Check library dependencies
dnl ---------------------------------------------------------------------------
PKG_CHECK_MODULES(GLIB, glib-2.0 >= 2.28.0 gobject-2.0 gthread-2.0 gio-2.0 >= 2.25.9)
PKG_CHECK_MODULES(GTK3, gtk+-3.0)
PKG_CHECK_MODULES(COLORD, colord >= 0.1.27)
PKG_CHECK_MODULES(LCMS, lcms2 >= 2.2)

dnl ---------------------------------------------------------------------------
dnl - Build Gtk+2 support
dnl ---------------------------------------------------------------------------
AC_ARG_ENABLE(gtk2, AS_HELP_STRING([--enable-gtk2],[build Gtk2 library]),
	      enable_gtk2=$enableval,enable_gtk2=no)
if test x$enable_gtk2 != xno; then
	PKG_CHECK_MODULES(GTK2, gtk+-2.0)
fi
AM_CONDITIONAL(HAVE_GTK2, [test "x$enable_gtk2" = "xyes"])

dnl ---------------------------------------------------------------------------
dnl - Build VALA support
dnl ---------------------------------------------------------------------------
AC_ARG_ENABLE(vala, AS_HELP_STRING([--enable-vala],[build vala bindings]),
	      enable_vala=$enableval,enable_vala=no)
if test x$found_introspection != xno -a x$enable_vala != xno; then
	AC_PATH_PROG([VAPIGEN], [vapigen], [])
	if test "x$VAPIGEN" = "x"; then
		has_vapigen="no"
		AC_MSG_WARN([vapigen not found, will not build Vala binding])
	else
		has_vapigen="yes"
	fi
else
	has_vapigen="no"
	if test x$found_introspection = xno; then
		AC_MSG_WARN([introspection not found, will not build Vala binding])
	fi
fi
AM_CONDITIONAL(HAVE_VAPIGEN, [test "x$has_vapigen" = "xyes"])

dnl ---------------------------------------------------------------------------
dnl - Is docbook2man available?
dnl ---------------------------------------------------------------------------
AC_PATH_PROG(DOCBOOK2MAN, docbook2man, no)
if test "$DOCBOOK2MAN" = "no" ; then
	AC_MSG_WARN([docbook2man not found, will not be able to build man documentation (if tarball, pre-generated documentation will be installed)])
fi
AM_CONDITIONAL(HAVE_DOCBOOK2MAN, [test "$DOCBOOK2MAN" != "no"])

dnl ---------------------------------------------------------------------------
dnl - Makefiles, etc.
dnl ---------------------------------------------------------------------------
AC_CONFIG_FILES([
Makefile
contrib/Makefile
doc/Makefile
doc/api/Makefile
doc/api/version.xml
man/Makefile
po/Makefile.in
client/Makefile
libcolord-gtk/cd-version.h
libcolord-gtk/colord-gtk.pc
libcolord-gtk/colord-gtk2.pc
libcolord-gtk/Makefile
])
AC_OUTPUT

dnl ==========================================================================
echo "
                    colord-gtk $VERSION
                  ===================

        prefix:                    ${prefix}
        datadir:                   ${datadir}
        compiler:                  ${CC}
        cflags:                    ${CFLAGS}
        cppflags:                  ${CPPFLAGS}
        gobject-introspection:     ${found_introspection}
        Vala API generator:        ${has_vapigen}
        Additional Gtk+2 support:  ${enable_gtk2}
"
