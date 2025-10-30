project(
  'base64',
  'c',
  version: '1.0.0',
  default_options: ['warning_level=3', 'werror=true']
)
incdir = include_directories('include')
c_files = files(
  'src/encode.c',
  'src/io.c',
  'src/decode.c'
)
base64_lib = both_libraries(
  'base64',
  c_files, include_directories: incdir,
  version: '1.0.0'
)
executable(
  'base64',
  'src/main.c',
  include_directories: incdir,
  link_with: base64_lib
)