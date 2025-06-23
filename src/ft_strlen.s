global ft_strlen
section .text
ft_strlen:
    test    rdi, rdi        ; Check for NULL
    jz      .null_input     ; If NULL, return 0
    mov     rcx, rdi        ; Copy pointer to string
    xor     rax, rax        ; length = 0
.loop:
    mov     dl, byte [rcx]  ; Load byte
    cmp     dl, 0           ; Check for null terminator
    je      .done
    inc     rcx             ; Next char
    inc     rax             ; length++
    jmp     .loop
.done:
    ret
.null_input:
    xor     rax, rax        ; Return 0
    ret 