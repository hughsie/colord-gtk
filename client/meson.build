executable(
  'cd-convert',
  sources : [
    'cd-convert.c',
  ],
  include_directories : [
    root_incdir,
    colord_gtk_incdir,
  ],
  dependencies : [
    glib,
    gio,
    gtk3,
    colord,
  ],
  link_with : colord_gtk,
  c_args : [
    '-DG_LOG_DOMAIN="Cd"',
    '-DVERSION="@0@"'.format(colord_gtk_version),
    '-DLOCALEDIR="@0@"'.format(get_option('localedir')),
  ],
  install : true,
  install_dir : bindir
)
