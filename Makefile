CFLAGS := -fno-stack-protector -fno-builtin -I ./include/libc -I ./include -nostdinc -ffreestanding

all: binary
clean:
	@rm -fR ./build/*
fclean: clean
	@rm -f binary
re: fclean all

start:
	@echo " [*] Building start"
	mkdir -p ./build
	nasm -f elf64 crt0.asm -o ./build/crt0.o
	@echo " [+] Done\n\n"

libc:
	@echo " [*] Building libc"
	mkdir -p ./build/src
	gcc -c $(CFLAGS) ./src/libc/unistd.c -o ./build/src/unistd.o
	gcc -c $(CFLAGS) ./src/libc/stdio.c -o ./build/src/stdio.o
	gcc -c $(CFLAGS) ./src/libc/stdlib.c -o ./build/src/stdlib.o
	gcc -c $(CFLAGS) ./src/libc/fcntl.c -o ./build/src/fcntl.o
	gcc -c $(CFLAGS) ./src/libc/sys/ptrace.c -o ./build/src/ptrace.o
	gcc -c $(CFLAGS) ./src/libc/string.c -o ./build/src/string.o
	@echo " [+] Done\n\n"

main:
	@echo " [*] Building main"
	mkdir -p ./build/src
	gcc -c $(CFLAGS) ./src/file_handler.c -o ./build/src/file_handler.o
	gcc -c $(CFLAGS) ./src/crypto.c -o ./build/src/crypto.o
	gcc -c $(CFLAGS) ./src/main.c -o ./build/src/main.o
	@echo " [+] Done\n\n"

binary: start libc main
	@echo " [*] Building binary"
	ld -e _start -o binary ./build/crt0.o ./build/src/*.o
	@echo " [+] Done"
