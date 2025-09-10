SECTION .text
    global _start
 
_start:
    ; Calls ptrace(PTRACE_TRACEME, 0, NULL, NULL)
    xor     rdi, rdi                ; request
    xor     rsi, rsi                ; pid
    xor     rdx, rdx                ; addr
    xor     r10, r10                ; data
    mov     rax, 101                ; syscall ptrace
    syscall

    ; Exits if the program is being debugged
    mov     rdi, rax
    xor     rax, rax ; Not to signal the error
    cmp     rdi, 0
    jne _exit

    ; Retrieve argc, argv, envp from stack
    mov     rdi, [rsp]             ; argc
    lea     rsi, [rsp + 8]         ; argv
	lea     rdx, [rsi + rdi*8 + 8] ; envp
 
    ; call main(argc, argv, envp)
    extern main
    call    main

_exit:
    ; system call exit(ret)
    mov     rdi, rax            ; main returned value
    mov     rax, 60             ; syscall exit
    syscall