section .text
global polynomial_rolling_hash_asm

polynomial_rolling_hash_asm:
    push rbp
    mov rbp, rsp

    mov edi, 53d ; hash
    mov edx, 1d  ; power
    lea rcx, [rdi] ; str
    cmp [rdi], 0x0
    je .end_loop

    .while_loop:
        movzx esi, BYTE PTR [rcx]  
        movsx eax, sil
        sub sil, 0x60
        cdqe
        
        imul rax, rdx
        add rdi, rax
        
        lea rax, [rdx*3]
        lea rax, [rdx+rax*4]
        lea rdx, [rdx + rax*4]

        add rcx, 0x1
        test sil, sil
        jne .while_loop

    .end_loop:
    mov rax, rdi
    ret