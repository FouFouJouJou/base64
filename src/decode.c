#include <stdio.h>
#include <stdlib.h>
#include <decode.h>
#include <assert.h>

uint8_t encoding_to_value(char c) {
  assert(c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c >= '0' && c <= '9' || c == '+' || c == '/');
  if (c >= 'A' && c <= 'Z') {
    return c-'A';
  }

  if (c >= 'a' && c <= 'z') {
    return c-'a'+26;
  }

  if (c >= '0' && c <= '9') {
    return c-'0'+52;
  }

  if (c == '+') {
    return 62;
  }
  if (c == '/') {
    return 63;
  }

  assert(0 && "UNREACHABLE");
}

void decode_block(char *input, char *output) {
  (void) output;
  uint8_t p1 = encoding_to_value(input[0]);
  uint8_t p2 = encoding_to_value(input[1]);
  uint8_t p3 = encoding_to_value(input[2]);
  uint8_t p4 = encoding_to_value(input[3]);
  printf("%d %d %d %d\n", p1, p2, p3, p4);

  char d1 = p1 << 2 | ((p2 >> 4) & 0x03);
  char d2 = (p2 & 0x0F) << 4 | ((p3 >> 2) & 0x0F);
  char d3 = p4 | (p3 & 0x3) << 6;

  output[0] = d1;
  output[1] = d2;
  output[2] = d3;
}

void decode_one_padding(char *input, char *output) {
  (void) input;
  (void) output;
}

void decode_two_padding(char *input, char *output) {
  (void) input;
  (void) output;
}

char *decode(char *input, ssize_t size) {
  (void) size;
  printf("size: %ld %ld\n", size, size/4);
  /* TODO: convert to dynamic string based on input */
  char *output = calloc(500, sizeof(char));
  decode_block(input, output);
  return output;
}
