#include "stdio.h"

int cypher(char *data, int data_len, const char key, int key_len) {
    int data_index, key_index;
    for (data_index = 0; data_index < size; data_index++) {
        printf("Before: %c\n", *data);
        *data = *data ^ *key;
        printf("After: %c\n", *data);
        data++;
        
    }
    return 0;
}

int decypher(char *data, const char *key, int size) {
    return 0;
}

int calculate_key(char *data, int size) {
    return 0;
}

int verify_key(char *data, int size, int key) {
    return 0;
}
