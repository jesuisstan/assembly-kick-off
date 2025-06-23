global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy
section .text
ft_strdup:
    test    rdi, rdi            ; Check src for NULL
    jz      .null_input         ; If NULL, return NULL
    push    rdi                 ; Save src on stack
    call    ft_strlen           ; Get length of src
    inc     rax                 ; include null terminator
    mov     rdi, rax            ; malloc(size)
    call    malloc wrt ..plt    ; Use wrt ..plt for malloc
    test    rax, rax            ; Check malloc result
    jz      .error              ; If NULL, handle error
    mov     rdi, rax            ; rdi = dest
    pop     rsi                 ; rsi = src (restore from stack)
    call    ft_strcpy           ; Copy src to dest
    ret
.error:
    pop     rdi                 ; Restore src from stack
.null_input:
    xor     rax, rax            ; Return NULL
    ret 