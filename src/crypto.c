#include "crypto.h"
#include <stdio.h>

char printables[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
int printables_len = 94;

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

// Sends back a random ascii character
long get_random_byte() {
    unsigned char buf;
    long ret;
    __asm__ volatile (
        "mov %1, %%rdi\n" // buf
        "mov $1, %%rsi\n" // len
        "xor %%rdx, %%rdx\n" // flags
        "mov $318, %%rax\n" // syscall: getrandom
        "syscall\n"
        : "=a"(ret)
        : "r"(&buf)
        : "rdi"
    );
    if (ret != 1) {
        return -1;
    }
    return printables[buf%printables_len];
}

int generate_password(char *dst, int data_len) {
    char c;
    for (int i = 0; i < data_len; i++) {
        c = get_random_byte();
        if (c == -1) {
            return -1;
        }
        dst[i] = c;
    }
    return 0;
}
