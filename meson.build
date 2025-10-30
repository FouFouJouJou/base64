project('base64',
  'c',
  version: '1.0',
  default_options: ['warning_level=3', 'werror=true']
)
incdir = include_directories('include')
c_files = files(
  'src/encode.c',
  'src/io.c',
  'src/decode.c'
)
base64_lib = shared_library(
  'base64',
  c_files, include_directories: incdir
)
executable(
  'base64',
  'src/main.c',
  include_directories: incdir,
  link_with: base64_lib
)