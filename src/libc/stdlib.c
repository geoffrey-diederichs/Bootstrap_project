#include "stdlib.h"
#include "string.h"

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

static void	*program_break = (void *)0;
static int	heap_size = 0;

void *sbrk(int increment)
{
	void *old_brk;

	if (program_break == 0)
	{
		__asm__ volatile (
				"mov $12, %%rax\n"
				"xor %%rdi, %%rdi\n"
				"syscall\n"
				: "=a"(program_break)
				:
				: "rdi"
				);
	}
	old_brk = program_break;
	program_break += increment;
	heap_size += increment;
	__asm__ volatile (
			"mov $12, %%rax\n"
			"syscall\n"
			:
			: "D"(program_break)
			:
			);
	return (old_brk);
}

void *malloc(size_t size)
{
	size = size + (8 - (size % 8)); // memory alignment on 8 bytes
	return (sbrk(size));
}

void *realloc(void *ptr, size_t size)
{
	void *new_pointer;

	new_pointer = my_malloc(size);
	strncpy(ptr, new_pointer, size); // will copy more than the original
	return (new_pointer);
}

void free(void)
{
	sbrk(-heap_size);
	heap_size = 0;
	program_break = 0;
}
