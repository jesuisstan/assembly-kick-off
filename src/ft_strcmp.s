global ft_strcmp
section .text
ft_strcmp:
    test    rdi, rdi        ; Check s1 for NULL
    jz      .null_input     ; If NULL, return 0
    test    rsi, rsi        ; Check s2 for NULL
    jz      .null_input     ; If NULL, return 0

.loop:
    mov     al, byte [rdi]  ; Load byte from s1
    mov     dl, byte [rsi]  ; Load byte from s2
    cmp     al, dl          ; Compare bytes
    jne     .diff           ; If not equal, return difference
    test    al, al          ; Check for end of string
    je      .done           ; If zero, strings are equal
    inc     rdi             ; Next char s1
    inc     rsi             ; Next char s2
    jmp     .loop
.diff:
    cmp     al, dl          ; Compare bytes again
    jl      .less           ; If s1 < s2, return -1
    mov     eax, 1          ; If s1 > s2, return 1
    ret
.less:
    mov     eax, -1         ; Return -1
    ret
.done:
    xor     eax, eax        ; Return 0
    ret
.null_input:
    xor     eax, eax        ; Return 0 for NULL input
    ret 