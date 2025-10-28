#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <encode.h>
#include <io.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    exit(1);
  }
  uint8_t input[1<<16];
  read_from_file(argv[1], input);
  char *result = encode((char *)input);
  printf("%s\n", result);
  free(result);
  return EXIT_SUCCESS;
}
