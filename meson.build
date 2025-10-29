project('base64', 'c', version: '1.0', default_options: ['warning_level=3', 'werror=true'])
incdir = include_directories('include')
c_sources = files('src/main.c', 'src/encode.c', 'src/io.c', 'src/decode.c')
executable('base64', c_sources, include_directories: incdir)