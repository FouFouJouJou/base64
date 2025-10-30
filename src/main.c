#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <encode.h>
#include <decode.h>
#include <io.h>

int main(int argc, char **argv) {
  int _encode=0, _decode=0;
  int input_file=0;
  int opt_len=0;
  char file_name[1<<8];
 /* TODO: definitely lookup more about getopt docs in description section about '+' & '-' and scanning modes. */
  opterr = 0;
  int opt;
  while((opt = getopt(argc, argv, "di:")) != -1) {
    switch(opt) {
    case 'i':
      input_file=1;
      opt_len = strlen(optarg);
      memcpy(file_name, optarg, opt_len);
      file_name[opt_len] = '\0';
      break;

    case 'd':
      _encode=0;
      _decode=1;
      break;
    default:
      break;
    }
  }

  if (!_decode && !_encode) {
    assert(argc == 2);
    input_file=1;
    int arg_len = strlen(argv[1]);
    memcpy(file_name, argv[1], arg_len);
    file_name[arg_len] = '\0';
    _encode=1;
  }

  if (_encode) {
#ifdef DEBUG
    printf("encoding\n");
#endif
    assert(!_decode && input_file);
    char input[1<<16];
    size_t size = read_from_file(file_name, input);
    char *encoding = encode(input, size);
    printf("%s\n", encoding);
    free(encoding);
  }

  if (_decode) {
#ifdef DEBUG
    printf("decoding\n");
#endif
    assert(!_encode && input_file);
    char input[1<<16];
    size_t size = read_from_file(file_name, input);
    char *decoding = decode(input, size);
    printf("%s\n", decoding);
    free(decoding);
  }

  return EXIT_SUCCESS;
}
