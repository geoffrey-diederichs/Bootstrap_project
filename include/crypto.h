#ifndef _CRYPTO_H
#define _CRYPTO_H

int cypher(char *data, const char *key, int size);
int decypher(char *data, const char *key, int size);
int calculate_key(char *data, int size);
int verify_key(char *data, int size, int key);

#endif