#ifndef _STDIO_H
#define _STDIO_H

#include "stddef.h"

int putchar(char c);
int puts(const char *str);
int putnbr(int num);
ssize_t getline(char **lineptr, size_t *n, int fd);
int puts_printf(const char *str);
int putnbr_printf(int num);
int printf(const char *format, ...);

#endif
