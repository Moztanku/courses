section .data
    n dd 1000
    primes db 1000 dup(0)
    buffer db 8 dup(0), 10, 0

section .text
    global _start

    _start:
        mov eax, 1
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        jmp _loop1

    _loop1:
        inc eax
        cmp eax, [n]
            jg _end

        mov ebx, primes
        sub ebx, 1
        jmp _loop2

    _loop2:
        inc ebx
        mov edx, [ebx]
        cmp edx, 0
            je _prime
        push eax
        xor edx, edx
        mov ecx, [ebx]
        div ecx
        pop eax
        cmp edx, 0
            jne _loop2
        jmp _loop1

    _prime:
        mov [ebx], eax
        jmp _loop1
    _end:
        mov ebx, primes
        sub ebx, 1
        call _print_loop1

        mov eax, 1
        mov ebx, 0
        int 0x80
    
    _print_loop1:
        inc ebx
        mov eax, [ebx]
        cmp eax, 0
            je _end_print_loop1
        call _print
        jmp _print_loop1

    _end_print_loop1:
        ret

    _print:
        push esp
        push ebp

        mov ebp, esp
        jmp _print_loop2
    _print_loop2:
        mov ebx, 10
        xor edx, edx
        div ebx
        add edx, 48
        push edx

        cmp eax, 0
            jne _print_loop2
        mov ebx, buffer
        jmp _put_in_buffer
    _put_in_buffer:
        pop eax
        mov [ebx], eax
        inc ebx
        cmp esp,ebp
            jne _put_in_buffer
        jmp _print_end

    _print_end:
        pop ebp
        pop esp 
        ret