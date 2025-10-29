#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <encode.h>
#include <stdint.h>

char value_to_encoding(uint8_t value) {
  assert(value <= 63);
  if (value <= 25) {
    return 'A'+value;
  }

  if (value >= 26 && value <= 51) {
    return 'a'+(value-26);
  }

  if (value >= 52 && value <= 61) {
    return '0'+(value-52);
  }

  if (value == 62) {
    return '+';
  }
  if (value == 63) {
    return '/';
  }
#ifdef DEBUG
  printf("%d\n", value);
#endif
  assert(0 && "UNREACHABLE");
}

void encode_block(char *string, char *output) {
  uint8_t p1 = (string[0]&0xFF)>>2;
  uint8_t p2 = (((string[0]&0xFF) & 0x03)<<4) | ((string[1] & 0xFF)>>4);
  uint8_t p3 = ((string[1] & 0x0F)<<2) | ((string[2]&0xFF)>>6);
  uint8_t p4 = (string[2] & 0xFF) & 0x3F;
  output[0]=value_to_encoding(p1);
  output[1]=value_to_encoding(p2);
  output[2]=value_to_encoding(p3);
  output[3]=value_to_encoding(p4);
}

void encode_one_padding(char *string, char *output) {
  uint8_t p1 = string[0]>>2;
  uint8_t p2 = (string[0] & 0x03)<<4 | (string[1]>>4);
  uint8_t p3 = (string[1] & 0x0F)<<2 ;
  output[0]=value_to_encoding(p1);
  output[1]=value_to_encoding(p2);
  output[2]=value_to_encoding(p3);
  output[3]='=';
}

void encode_two_paddings(char *string, char *output) {
  uint8_t p1 = (string[0] & 0xFF)>>2;
  uint8_t p2 = ((string[0]& 0xFF) & 0x03)<<4;
  output[0]=value_to_encoding(p1);
  output[1]=value_to_encoding(p2);
  output[2]=output[3]='=';
}

int encoded_result_length(ssize_t input_size) {
  int total_bits = input_size*8;
/* #ifdef DEBUG */
  int missing_bits = total_bits%24;
/* #endif */
  int total_padding = total_bits%3;
  int total_complete_blocks = total_bits/24;
/* #ifdef DEBUG */
  printf("total bytes: %zd\n", input_size);
  printf("total bits: %d\n", total_bits);
  printf("missing bits: %d\n", missing_bits);
  printf("total padding: %d\n", total_padding);
  printf("total complete blocks: %d\n", total_complete_blocks);
/* #endif */
  return (total_complete_blocks*4) + (total_padding != 0 ? 4 : 0);
}

char *encode(char *input, ssize_t input_size) {
  size_t total_bits = input_size*8;
  size_t total_complete_blocks = total_bits/24;
  size_t total_padding = total_bits%3;
  size_t input_idx=0, output_idx=0;

  int l = encoded_result_length(input_size);
  char *output = calloc(l, sizeof(char));

  for (size_t i=0; i<total_complete_blocks; ++i) {
    encode_block(input+input_idx, output+output_idx);
    input_idx+=3;
    output_idx+=4;
  }

  if (total_padding == 1) {
    encode_one_padding(input+input_idx, output+output_idx);
  }
  else if (total_padding == 2) {
    encode_two_paddings(input+input_idx, output+output_idx);
  }
  return output;
}
