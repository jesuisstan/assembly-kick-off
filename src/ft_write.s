global ft_write
extern __errno_location
section .text
ft_write:
    ; rdi = fd, rsi = buf, rdx = count
    test    rsi, rsi            ; Check buf for NULL
    jz      .null_buf           ; If NULL, set errno=EFAULT, return -1
    mov     rax, 1              ; syscall: write
    mov     r10, rdx            ; syscall arg3
    syscall
    cmp     rax, 0
    jl      .error              ; If rax < 0, error
    ret

.null_buf:
    mov     edi, 14             ; EFAULT = 14 ; set errno to EFAULT
    call    qword [rel __errno_location wrt ..gotpc] ; get the address of errno (qword = 8 bytes, rel = relative)
    mov     dword [rax], edi    ; *errno = EFAULT ; set errno to EFAULT (dword = 4 bytes)
    mov     rax, -1             ; return -1
    ret

.error:
    neg     rax                 ; rax = -errno ; negate rax to get the error number
    mov     edi, eax            ; edi = errno ; move the error number to edi
    call    qword [rel __errno_location wrt ..gotpc] ; get the address of errno (qword = 8 bytes)
    mov     dword [rax], edi    ; *errno = errno ; set *errno_ptr = error_code (dword = 4 bytes)
    mov     rax, -1             ; return -1
    ret 