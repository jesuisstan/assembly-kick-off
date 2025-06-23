global ft_strcpy
section .text
ft_strcpy:
    test    rdi, rdi        ; Check dst for NULL
    jz      .null_input     ; If NULL, return NULL
    test    rsi, rsi        ; Check src for NULL
    jz      .null_input     ; If NULL, return NULL
    mov     rax, rdi        ; Save dst for return
.copy_loop:
    mov     dl, byte [rsi]  ; Load byte from src
    mov     byte [rdi], dl  ; Copy to dst
    inc     rsi             ; Next char src
    inc     rdi             ; Next char dst
    test    dl, dl          ; Check for end of string
    jnz     .copy_loop
    ret
.null_input:
    xor     rax, rax        ; Return NULL
    ret 