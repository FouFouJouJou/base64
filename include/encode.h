#ifndef __ENCODE_H__
#define __ENCODE_H__
#define ENCODE_INPUT "I love the way you lie"
#include <stdint.h>

char value_to_encoding(uint8_t value);
void encode_block(char *string, char *output);
void encode_one_padding(char *input, char *output);
void encode_two_padding(char *input, char *output);
int encoded_result_length(ssize_t size);
char *encode(char *input, ssize_t size);

#endif
