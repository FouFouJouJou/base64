#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <encode.h>
#include <decode.h>
#include <io.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    exit(1);
  }
  char input[1<<16];
  size_t size = read_from_file(argv[1], input);
  printf("Encoding: %s", input);
  char *encoding = encode(input, size);
  printf("Base64: %s\n", encoding);
  char *decoding = decode(encoding, strlen(encoding));
  printf("Decoding: %s", decoding);
  free(encoding);
  free(decoding);
  return EXIT_SUCCESS;
}
