#ifndef _STDLIB_H
#define _STDLIB_H

#include "stddef.h"

[[noreturn]] void exit(int status);
void *sbrk(int increment);
void *malloc(size_t size);
void free(void);

#endif
