#ifndef _CRYPTO_H
#define _CRYPTO_H

#include "stdbool.h"

int cypher(char *src, char *dst, int data_len, char *key, int key_len);
int calculate_signature(char *data, int size);
bool verify_signature(char *data, int size, int key);
long get_random_byte();
int generate_password(char *dst, int data_len);

#endif