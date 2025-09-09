#ifndef _FCNTL_H
#define _FCNTL_H

#define O_RDONLY  0
#define O_WRONLY  1
#define O_RDWR    2

typedef unsigned int mode_t;
int open(const char *pathname, int flags, mode_t mode);

#endif
