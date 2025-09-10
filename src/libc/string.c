#include "stdio.h"
#include "string.h"

int strcmp(const char *s1, const char *s2) {
    int cmp;
    while ((*s1) || (*s2)) {
        cmp = *s1++ - *s2++;
        if (cmp != 0) {
            return cmp;
        }
    }

    return cmp;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    int cmp, i;
    for (i = 0; i < n; i++) {
        cmp = *s1++ - *s2++;
        if (cmp != 0) {
            return cmp;
        }
    }

    return cmp;
}
