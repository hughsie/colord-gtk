xsltproc = find_program('xsltproc')

stylesheet_url = 'http://docbook.sourceforge.net/release/xsl-ns/current/manpages/docbook.xsl'
ret = run_command(xsltproc, '--nonet', stylesheet_url)
if ret.returncode() != 0
  error('Cannot build man pages without docbook-xsl-ns')
endif

xsltproc_args = [
  xsltproc,
  '--output', '@OUTPUT@',
  '--nonet',
  '--stringparam', 'man.authors.section.enabled', '0',
  '--stringparam', 'man.copyright.section.enabled', '0',
  '--stringparam', 'man.output.quietly', '1',
  '--stringparam', 'man.th.extra1.suppress', '1',
  '--stringparam', 'funcsynopsis.style', 'ansi',
  stylesheet_url,
  '@INPUT@',
]

custom_target(
  'cd-convert-man',
  input : 'cd-convert.xml',
  output : '@BASENAME@.1',
  command : xsltproc_args,
  install : true,
  install_dir : join_paths(mandir, 'man1'),
)
