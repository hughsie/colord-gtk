man_MANS_DIST = 					\
	cd-convert.1

EXTRA_DIST =						\
	cd-convert.sgml					\
	$(man_MANS_DIST)

if HAVE_DOCBOOK2MAN
man_MANS =						\
	$(man_MANS_DIST)
endif

if HAVE_DOCBOOK2MAN
cd-convert.1: cd-convert.sgml
	$(AM_V_GEN)					\
	docbook2man $? > /dev/null
endif

MAINTAINERCLEANFILES =					\
	manpage.links					\
	manpage.log					\
	manpage.refs					\
	$(man_MANS)

clean-local :
	rm -f *~
	rm -f *.1
	rm -f manpage.*

-include $(top_srcdir)/git.mk
