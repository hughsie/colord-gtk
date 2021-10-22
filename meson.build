project('colord-gtk', 'c',
  version : '0.2.1',
  license : 'LGPL-2.1+',
  meson_version : '>=0.46.0',
  default_options : ['c_std=c99']
)

colord_gtk_version = meson.project_version()
varr = colord_gtk_version.split('.')
colord_gtk_major_version = varr[0]
colord_gtk_minor_version = varr[1]
colord_gtk_micro_version = varr[2]

conf = configuration_data()
conf.set('CD_GTK_MAJOR_VERSION', colord_gtk_major_version)
conf.set('CD_GTK_MINOR_VERSION', colord_gtk_minor_version)
conf.set('CD_GTK_MICRO_VERSION', colord_gtk_micro_version)
conf.set_quoted('PACKAGE_VERSION', colord_gtk_version)

# libtool versioning - this applies to libcolord
#
# See http://sources.redhat.com/autobook/autobook/autobook_91.html#SEC91 for details
#
# - If interfaces have been changed or added, but binary compatibility
#   has been preserved, change:
#      CURRENT += 1
#      REVISION = 0
#      AGE += 1
# - If binary compatibility has been broken (eg removed or changed
#   interfaces), change:
#      CURRENT += 1
#      REVISION = 0
#      AGE = 0
# - If the interface is the same as the previous version, but bugs are
#   fixed, change:
#      REVISION += 1
lt_current = '1'
lt_revision = '3'
lt_age = '0'
lt_version = '@0@.@1@.@2@'.format(lt_current, lt_age, lt_revision)

# get supported warning flags
test_args = [
  '-fstack-protector-strong',
  '-Waggregate-return',
  '-Wunused',
  '-Warray-bounds',
  '-Wcast-align',
  '-Wclobbered',
  '-Wdeclaration-after-statement',
  '-Wempty-body',
  '-Wextra',
  '-Wformat=2',
  '-Wformat-nonliteral',
  '-Wformat-security',
  '-Wformat-signedness',
  '-Wignored-qualifiers',
  '-Wimplicit-function-declaration',
  '-Winit-self',
  '-Wmissing-declarations',
  '-Wmissing-format-attribute',
  '-Wmissing-include-dirs',
  '-Wmissing-noreturn',
  '-Wmissing-parameter-type',
  '-Wmissing-prototypes',
  '-Wnested-externs',
  '-Wno-discarded-qualifiers',
  '-Wno-missing-field-initializers',
  '-Wno-strict-aliasing',
  '-Wno-suggest-attribute=format',
  '-Wno-unused-parameter',
  '-Wold-style-definition',
  '-Woverride-init',
  '-Wpointer-arith',
  '-Wreturn-type',
  '-Wshadow',
  '-Wsign-compare',
  '-Wstrict-aliasing',
  '-Wstrict-prototypes',
  '-Wswitch-default',
  '-Wtype-limits',
  '-Wundef',
  '-Wuninitialized',
  '-Wunused-but-set-variable',
  '-Wwrite-strings'
]

cc = meson.get_compiler('c')
foreach arg: test_args
  if cc.has_argument(arg)
    add_project_arguments(arg, language : 'c')
  endif
endforeach

glib = dependency('glib-2.0', version : '>= 2.28.0')
gio = dependency('gio-2.0', version : '>= 2.25.9Z')
gtk3 = dependency('gtk+-3.0')
colord = dependency('colord', version : '>= 0.1.27')

if get_option('gtk2')
  gtk2 = dependency('gtk+-2.0')
  conf.set('HAVE_GTK2', '1')
endif

if get_option('gtk4')
  gtk4 = dependency('gtk4', version : '>= 4.4')
endif

gnome = import('gnome')
i18n = import('i18n')

add_project_arguments('-DCD_COMPILATION', language: 'c')

prefix = get_option('prefix')

bindir = join_paths(prefix, get_option('bindir'))
libdir = join_paths(prefix, get_option('libdir'))
datadir = join_paths(prefix, get_option('datadir'))
libexecdir = join_paths(prefix, get_option('libexecdir'))
localstatedir = join_paths(prefix, get_option('localstatedir'))
sysconfdir = join_paths(prefix, get_option('sysconfdir'))
mandir = join_paths(prefix, get_option('mandir'))
includedir = join_paths(prefix, get_option('includedir'))

conf.set_quoted('SYSCONFDIR', sysconfdir)
conf.set_quoted('BINDIR', bindir)
conf.set_quoted('LIBDIR', libdir)
conf.set_quoted('DATADIR', datadir)
conf.set_quoted('LIBEXECDIR', libexecdir)
conf.set_quoted('LOCALSTATEDIR', localstatedir)

conf.set_quoted('GETTEXT_PACKAGE', meson.project_name())
conf.set_quoted('PACKAGE_NAME', meson.project_name())
conf.set_quoted('VERSION', meson.project_version())
conf.set_quoted('LOCALEDIR', get_option('localedir'))

configure_file(
  output : 'config.h',
  configuration : conf
)

root_incdir = include_directories('.')

subdir('libcolord-gtk')
subdir('po')

subdir('client')
if get_option('docs')
  subdir('doc')
endif
if get_option('man')
  subdir('man')
endif
