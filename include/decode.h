#ifndef __DECODE_H__
#define __DECODE_H__
#include <stdio.h>
#include <stdint.h>

void decode_block(char *input, char *output);
void decode_one_padding(char *input, char *output);
void decode_double_padding(char *input, char *output);
char *decode(char *input, size_t size);
uint8_t encoding_to_value(char c);

#endif
