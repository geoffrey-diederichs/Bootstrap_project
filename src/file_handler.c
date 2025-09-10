#include "fcntl.h"
#include "unistd.h"
#include "stddef.h"

char buf[1024] = {0};

char *open_db(const char *filename) {
    int fd = open(filename, O_RDONLY | O_CREAT, 0644);
    if (fd < 0) {
        return NULL;
    }

    char *buf = malloc(1);
    for (int i = 0; i < 1023; i++) {
        if (read(fd, &buf[i], 1) != 1) break;
        
    }

    close(fd);
    return buf;
}
