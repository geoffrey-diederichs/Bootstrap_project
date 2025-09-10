#ifndef _PTRACE_H
#define _PTRACE_H

#include "stdlib.h"

#define PTRACE_TRACEME 0
#define ANTI_DEBUG() if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) exit(1);

long ptrace(long request, long pid, void *addr, void *data);

#endif
