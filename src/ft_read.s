global ft_read
extern __errno_location
section .text
ft_read:
    ; rdi = fd, rsi = buf, rdx = count
    test    rsi, rsi            ; Check buf for NULL
    jz      .null_buf           ; If NULL, set errno=EFAULT, return -1
    mov     rax, 0              ; syscall: read
    mov     r10, rdx            ; syscall arg3
    syscall
    cmp     rax, 0
    jl      .error              ; If rax < 0, error
    ret

.null_buf:
    mov     edi, 14             ; EFAULT = 14
    call    qword [rel __errno_location wrt ..gotpc]
    mov     dword [rax], edi    ; *errno = EFAULT
    mov     rax, -1
    ret

.error:
    neg     rax                 ; rax = -errno
    mov     edi, eax            ; edi = errno
    call    qword [rel __errno_location wrt ..gotpc]
    mov     dword [rax], edi    ; *errno = errno
    mov     rax, -1
    ret 