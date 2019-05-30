version_xml = configure_file(
  input : 'version.xml.in',
  output : 'version.xml',
  configuration : conf,
)

gnome.gtkdoc(
  'colord-gtk',
  src_dir : [
    join_paths(meson.source_root(), 'libcolord-gtk'),
    join_paths(meson.build_root(), 'libcolord-gtk'),
  ],
  main_xml : 'colord-gtk-docs.xml',
  content_files : [
    '../../COPYING',
    version_xml,
  ],
  install : true
)
