#ifndef __ENCODE_H__
#define __ENCODE_H__
#define ENCODE_INPUT "I love the way you lie"

char value_to_encoding(int value);
void encode_block(char *string, char *output);
void encode_one_padding(char *input, char *output);
void encode_two_padding(char *input, char *output);
int encoded_result_length(char *input);
char *encode(char *input);

#endif
