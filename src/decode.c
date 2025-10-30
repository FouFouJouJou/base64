#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <decode.h>
#include <assert.h>

uint8_t encoding_to_value(char c) {
  assert((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '+' || c == '/');
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
  /* printf("%d %d %d %d\n", p1, p2, p3, p4); */

  char d1 = p1 << 2 | ((p2 >> 4) & 0x03);
  char d2 = (p2 & 0x0F) << 4 | ((p3 >> 2) & 0x0F);
  char d3 = p4 | (p3 & 0x3) << 6;

  output[0] = d1;
  output[1] = d2;
  output[2] = d3;
}

void decode_one_padding(char *input, char *output) {
  uint8_t p1 = encoding_to_value(input[0]);
  uint8_t p2 = encoding_to_value(input[1]);
  uint8_t p3 = encoding_to_value(input[2]);

  char d1 = p1 << 2 | ((p2 >> 4) & 0x03);
  char d2 = (p2 & 0x0F) << 4 | ((p3 >> 2) & 0x0F);
  output[0] = d1;
  output[1] = d2;
}

void decode_double_padding(char *input, char *output) {
  uint8_t p1 = encoding_to_value(input[0]);
  uint8_t p2 = encoding_to_value(input[1]);

  char d1 = p1 << 2 | ((p2 >> 4) & 0x03);
  output[0] = d1;
}

char *decode(char *input, size_t size) {
  int total_blocks = size/4;
  int base_idx = input[size-1] == '\n' ? size-2 : size-1;
  int is_double_padding = !strncmp(input+base_idx-1, "==", 2);
  int is_one_padding = !is_double_padding && !strncmp(input+base_idx, "=", 1);
  total_blocks-=(is_one_padding || is_double_padding) ? 1 : 0;
  int input_idx=0, output_idx=0;
#ifdef DEBUG
  printf("size: %ld\n", size);
  printf("total blocks: %d\n", total_blocks);

  printf("one padding: %d\n", is_one_padding);
  printf("two padding: %d\n", is_double_padding);
#endif
  /* TODO: convert to dynamic string based on input */
  size_t output_size = total_blocks*3;
  if (is_one_padding) {
    output_size+=2;
  }
  else if (is_double_padding) {
    output_size+=1;
  }
  char *output = calloc(output_size, sizeof(char));
  for (int i=0; i<total_blocks; ++i) {
    decode_block(input+input_idx, output+output_idx);
    input_idx+=4;
    output_idx+=3;
  }

  if (is_one_padding) {
    decode_one_padding(input+input_idx, output+output_idx);
    output_idx+=2;
  }
  else if (is_double_padding) {
    decode_double_padding(input+input_idx, output+output_idx);
    output_idx+=1;
  }

  assert((size_t) output_idx == output_size);
  output[output_size] = '\0';
  return output;
}
