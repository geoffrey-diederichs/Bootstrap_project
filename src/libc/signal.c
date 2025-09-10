#include "signal.h"

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {
    long ret;
    register unsigned long r10_in __asm__("r10") = 8UL;

    __asm__ volatile (
        "mov %1, %%rdi\n" // signum
        "mov %2, %%rsi\n" // act
        "mov %3, %%rdx\n" // oldact
        "mov $13, %%rax\n" // syscall sigaction
        "syscall\n"
        : "=a"(ret)
        : "r"((long)signum), "r"(act), "r"(oldact), "r"(r10_in)
        : "rdi", "rsi", "rdx", "rcx"
    );

    return (int)ret;
}
