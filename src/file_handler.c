#include "fcntl.h"
#include "unistd.h"
#include "stddef.h"
#include "stdlib.h"

unsigned long long ullong_max = 18446744073709551615ULL;

char *open_db(const char *filename) {
    int fd = open(filename, O_RDONLY | O_CREAT, 0644);
    if (fd < 0) {
        return NULL;
    }

    unsigned long long size = 24;
    unsigned long long index = 0;
    char *buf = malloc(size);
    if (!buf) { 
        close(fd); 
        return NULL;
    }

    while (read(fd, &buf[index], 1) == 1) {
        index ++;
        if (index == size) {
            if (size >= ullong_max) {
                free();
                close(fd);
                return NULL;
            } else {
                size += 24;
                buf = realloc(buf, size);
                if (!buf) {
                    free();
                    close(fd); 
                    return NULL;
                }
            }
        }
    }
    buf[index] = 0;

    close(fd);
    return buf;
}

size_t save_db(const char *filename, const char *data, unsigned long long size) {
    int fd = open(filename, O_RDONLY | O_CREAT, 0644);
    if (fd < 0) {
        return -1;
    }

    size_t ret = write(fd, data, size);
    close(fd);
    return ret;
}
