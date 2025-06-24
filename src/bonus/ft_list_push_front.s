; ft_list_push_front(t_list **begin_list, void *data)
; rdi = begin_list, rsi = data
global ft_list_push_front
extern malloc
section .text
ft_list_push_front:
    push r12                ; Preserve r12 (callee-saved)
    push r13                ; Preserve r13 (callee-saved)

    test rdi, rdi           ; Check if begin_list is NULL
    jz .return_safe

    mov r12, rdi            ; Save begin_list in callee-saved register
    mov r13, rsi            ; Save data in callee-saved register

    ; Create new element
    mov rdi, 16             ; sizeof(t_list) on 64-bit
    call malloc wrt ..plt
    test rax, rax           ; Check malloc result
    jz .return_safe         ; If malloc fails, do nothing

    ; new->data = data
    mov [rax], r13
    ; new->next = *begin_list
    mov r10, [r12]
    mov [rax + 8], r10
    ; *begin_list = new
    mov [r12], rax

.return_safe:
    pop r13                 ; Restore r13
    pop r12                 ; Restore r12
    ret 