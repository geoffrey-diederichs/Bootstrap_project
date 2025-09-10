long ptrace(long request, long pid, void *addr, void *data) {
    long ret;
    __asm__ volatile (
        "mov %1, %%rdi\n" // request
        "mov %2, %%rsi\n" // pid
        "mov %3, %%rdx\n" // addr
        "mov %4, %%r10\n" // data
        "mov $101, %%rax\n" // syscall: ptrace (x86_64)
        "syscall\n"
        : "=a"(ret)
        : "r"(request), "r"(pid), "r"(addr), "r"(data)
        : "rdi", "rsi", "rdx", "r10"
    );
    return ret;
}
