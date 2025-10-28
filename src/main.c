#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define INPUT "I love the way you lie"
#define ENCODED_INPUT "SSBsb3ZlIHRoZSB3YXkgeW91IGxpZQ=="

char value_to_encoding(int value) {
  assert(value >= 0 && value <= 63);
  if (value >= 0 && value <= 25) {
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
    return '-';
  }
  printf("%d\n", value);
  assert(0 && "UNREACHABLE");
}

void encode_block(char *string) {
  int p1 = string[0]>>2;
  int p2 = (string[0] & 0x03)<<4 | (string[1]>>4);
  int p3 = (string[1] & 0x0F)<<2 | (string[2]>>6);
  int p4 = string[2] & 0x3F;
  printf("%c%c%c%c", value_to_encoding(p1), value_to_encoding(p2), value_to_encoding(p3), value_to_encoding(p4));
}

void encode_one_padding(char *string) {
  int p1 = string[0]>>2;
  int p2 = (string[0] & 0x03)<<4 | (string[1]>>4);
  int p3 = (string[1] & 0x0F)<<2 ;
  printf("%c%c%c=", value_to_encoding(p1), value_to_encoding(p2), value_to_encoding(p3));
}

void encode_two_paddings(char *string) {
  int p1 = string[0]>>2;
  int p2 = (string[0] & 0x03)<<4;
  printf("%c%c==", value_to_encoding(p1), value_to_encoding(p2));
}

char *encode(char *string) {
  size_t string_size = strlen(string);
  int total_bits = string_size*8;
  int missing_bits = total_bits%24;
  int total_padding = total_bits%3;
  int total_complete_blocks = total_bits/24;
  int idx=0;
  printf("total bits: %d\n", total_bits);
  printf("missing bits: %d\n", missing_bits);
  printf("total padding: %d\n", total_padding);
  printf("total complete blocks: %d\n", total_complete_blocks);
  for (int i=0; i<total_complete_blocks; ++i) {
    encode_block(string+idx);
    idx+=3;
  }

  if (total_padding == 1) {
    encode_one_padding(string+idx);
  }
  else if (total_padding == 2) {
    encode_two_paddings(string+idx);
  }
  printf("\n");
  return 0;
}

int main() {
  printf("Base64 encoding: %s\n", INPUT);
  printf("%ld %ld\n", sizeof(ENCODED_INPUT), strlen(ENCODED_INPUT));
  assert(value_to_encoding(0) == 'A');
  assert(value_to_encoding(10) == 'K');
  assert(value_to_encoding(26) == 'a');
  assert(value_to_encoding(34) == 'i');
  assert(value_to_encoding(62) == '+');
  printf("encoding: %s\n", encode(INPUT));
  // assert(strncmp(encode(INPUT), ENCODED_INPUT, strlen(ENCODED_INPUT)) == 0);
  return EXIT_SUCCESS;
}
