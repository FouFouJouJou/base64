#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define INPUT "I love the way you lie"
#define ENCODED_INPUT "SSBsb3ZlIHRoZSB3YXkgeW91IGxpZQ=="

char value_to_encoding(int value) {
  assert(value >= 0 && value <= 63);
  if (value >= 0 && value < 26) {
    return 'A'+value;
  }

  if (value >= 26 && value < 52) {
    return 'a'+(value-26);
  }

  if (value == 62) {
    return '+';
  }
  if (value == 63) {
    return '-';
  }
  assert(0 && "UNREACHABLE");
}

char *encode(char *string) {
  (void) string;
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
  assert(strncmp(encode(INPUT), ENCODED_INPUT, strlen(ENCODED_INPUT)) == 0);
  return EXIT_SUCCESS;
}
