section .data
    number db "0123456789ABCDEF"
    buffer db 8 dup(0), 10, 0

section .text
    global _start

    _start:
        xor rdx, rdx
        mov rax, 14440 ; input
        mov rbp, rsp
        jmp _put_on_stack
    _put_on_stack:
        mov rbx, 16
        xor rdx, rdx
        div rbx
        push rdx

        cmp rax, 0
        jne _put_on_stack

        mov rbx, buffer
        jmp _put_in_buffer
    _put_in_buffer:
        pop rax
        add rax, number
        mov al, [rax]
        mov [rbx], al
        inc rbx

        cmp rsp, rbp
        jne _put_in_buffer

        jmp _end
    _end:
        mov rax, 1
        mov rdi, 1
        mov rsi, buffer
        mov rdx, 10
        syscall   ;write(1, buffer, 8)

        mov rax, 60
        mov rdi, 0
        syscall   ;exit(0)