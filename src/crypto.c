#include "crypto.h"
#include <stdio.h>

int cypher(char *src, char *dst, int data_len, char *key, int key_len) {
    for (int i = 0; i < data_len; i++) {
        dst[i] = src[i] ^ key[i%key_len];
    }
    return 0;
}

int calculate_signature(char *data, int size) {
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum = (sum + data[i]) % 10000;
    }
    return sum;
}

bool verify_signature(char *data, int size, int key) {
    if (calculate_signature(data, size) == key) {
        return true;
    }
    return false;
}
