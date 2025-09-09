[[noreturn]] void exit(int status) {
    __asm__ volatile (
        "mov $0x3c, %%rax\n" // syscall: exit
        "movl %0, %%edi\n" // status
        "syscall\n"
        :
        : "r"(status)
        : "%rax", "%rdi"
    );
    __builtin_unreachable();
}
