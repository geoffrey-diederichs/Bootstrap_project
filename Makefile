CFLAGS := -fno-stack-protector -fno-builtin -I ./include/libc

all: binary
clean:
	@rm -fR ./build/*
fclean: clean
	@rm -f binary
re: fclean all

start:
	@echo -ne " [*] Building start\n"
	mkdir -p ./build
	nasm -f elf64 crt0.asm -o ./build/crt0.o
	@echo -ne " [+] Done\n\n"

libc:
	@echo -ne " [*] Building libc\n"
	mkdir -p ./build/src
	@echo -ne " [+] Done\n\n"

main:
	@echo -ne " [*] Building main\n"
	mkdir -p ./build/src
	gcc -c $(CFLAGS) ./src/main.c -o ./build/src/main.o
	@echo -ne " [+] Done\n\n"

binary: start libc main
	@echo -ne " [*] Building binary\n"
	ld -e _start -o binary ./build/crt0.o ./build/src/*.o
	@echo -ne " [+] Done\n\n"