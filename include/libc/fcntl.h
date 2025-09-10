#ifndef _FCNTL_H
#define _FCNTL_H

#define O_RDONLY  0
#define O_WRONLY  1
#define O_RDWR    2
#define O_CREAT   00000100
#define O_APPEND  02000

typedef unsigned int mode_t;
int open(const char *pathname, int flags, mode_t mode);

#endif
