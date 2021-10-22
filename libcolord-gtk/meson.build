cargs = [
  '-DG_LOG_DOMAIN="libcolord-gtk"',
]

colord_gtk_version_h = configure_file(
  input : 'cd-version.h.in',
  output : 'cd-version.h',
  configuration : conf,
)

install_headers(
  'colord-gtk.h',
  subdir : 'colord-1',
)

colord_gtk_incdir = include_directories('.')

install_headers([
    'cd-sample-widget.h',
    'cd-sample-window.h',
    'cd-window.h',
    'cd-window-sync.h',
    colord_gtk_version_h,
  ],
  subdir : 'colord-1/colord-gtk',
)

colord_gtk = shared_library(
  'colord-gtk',
  sources : [
    'cd-sample-widget.c',
    'cd-sample-window.c',
    'cd-window.c',
    'cd-window-sync.c',
  ],
  soversion : lt_current,
  version : lt_version,
  dependencies : [
    glib,
    gio,
    gtk3,
    colord,
  ],
  c_args : [
    cargs,
  ],
  include_directories : [
    root_incdir,
  ],
  install : true
)

pkgg = import('pkgconfig')
pkgg.generate(
  libraries : colord_gtk,
  requires : [ 'colord', 'gtk+-3.0' ],
  subdirs : 'colord-1',
  version : meson.project_version(),
  name : 'colord-gtk',
  filebase : 'colord-gtk',
  description : 'colord-gtk is GTK integration for libcolord',
)

if get_option('introspection')
libcolord_gtk_gir = gnome.generate_gir(
  colord_gtk,
  sources : [
    'cd-sample-widget.c',
    'cd-sample-widget.h',
    'cd-sample-window.c',
    'cd-sample-window.h',
    'cd-window.c',
    'cd-window.h',
    'cd-window-sync.c',
    'cd-window-sync.h',
    colord_gtk_version_h,
  ],
  nsversion : '1.0',
  namespace : 'ColordGtk',
  symbol_prefix : 'cd',
  identifier_prefix : 'Cd',
  export_packages : 'colord-gtk',
  extra_args : [
    '--c-include=colord-gtk.h',
    '-DCD_COMPILATION',
    ],
  dependencies : [
    glib,
    gio,
    gtk3,
    colord,
  ],
  includes : [
    'GObject-2.0',
    'Gio-2.0',
    'Gtk-3.0',
    'Colord-1.0',
  ],
  install : true
)
endif

if get_option('vapi')
  gnome.generate_vapi(
    'colord-gtk',
    sources: libcolord_gtk_gir[0],
    packages: [ 'glib-2.0', 'gio-2.0', 'gtk+-3.0', 'colord' ],
    install: true,
  )
endif

if get_option('gtk2')
  colord_gtk2 = shared_library(
    'colord-gtk2',
    sources : [
      'cd-window.c',
      'cd-window-sync.c',
    ],
    soversion : lt_current,
    version : lt_version,
    dependencies : [
      glib,
      gio,
      gtk2,
      colord,
    ],
    c_args : [
      cargs,
    ],
    include_directories : [
      root_incdir,
    ],
    install : true
  )

  pkgg.generate(
    libraries : colord_gtk2,
    requires : [ 'colord', 'gtk+-2.0' ],
    subdirs : 'colord-1',
    version : meson.project_version(),
    name : 'colord-gtk2',
    filebase : 'colord-gtk2',
    description : 'colord-gtk is GTK2 integration for libcolord',
  )
endif

if get_option('tests')
  e = executable(
    'colord-gtk-test',
    sources : [
      'cd-self-test.c',
    ],
    include_directories : [
      root_incdir,
    ],
    dependencies : [
      glib,
      gio,
      gtk3,
      colord,
    ],
    link_with : colord_gtk,
    c_args : [
      cargs,
    ]
  )
test('colord-test-private', e)
endif
