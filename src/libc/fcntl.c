#include "fcntl.h"

int open(const char *pathname, int flags, mode_t mode) {
    long ret;
    __asm__ volatile (
        "mov %1, %%rdi\n" // pathname
        "mov %2, %%rsi\n" // flags
        "mov %3, %%rdx\n" // mode
        "mov $2, %%rax\n" // syscall: open
        "syscall\n"
        : "=a"(ret)
        : "r"(pathname), "r"((long)flags), "r"((long)mode)
        : "rdi", "rsi", "rdx"
    );

    return ret;
}
