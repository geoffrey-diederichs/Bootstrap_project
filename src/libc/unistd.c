#include "unistd.h"
#include "sys/ptrace.h"

ssize_t write(int fd, const void *str, size_t len) {
    long ret;
    __asm__ volatile (
        
        "mov %1, %%rdi\n" // fd
        "mov %2, %%rsi\n" // str
        "mov %3, %%rdx\n" // len
        "mov $1, %%rax\n" // syscall: write/*
        "syscall\n"
        : "=a"(ret)
        : "r"((long)fd), "r"(str), "r"(len)
        : "rdi", "rsi", "rdx"
    );

    return ret;
}

ssize_t read(int fd, void *buf, size_t count) {
    long ret;
    __asm__ (
        "mov %1, %%rdi\n" // fd
        "mov %2, %%rsi\n" // buf
        "mov %3, %%rdx\n" // count
        "mov $0, %%rax\n" // syscall: read
        "syscall\n"
        : "=a"(ret)
        : "r"((long)fd), "r"(buf), "r"(count)
        : "rdi", "rsi", "rdx"
    );
    
    return ret;
}

int close(int fd) {
    long ret;
    __asm__ volatile (
        "mov %1, %%rdi\n" // fd
        "mov $3, %%rax\n" // syscall: close
        "syscall\n"
        : "=a"(ret)
        : "r"((long)fd)
        : "rdi"
    );

    return ret;
}
