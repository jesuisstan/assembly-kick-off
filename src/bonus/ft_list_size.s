; int ft_list_size(t_list *begin_list)
; rdi = begin_list
global ft_list_size
section .text
ft_list_size:
    xor rax, rax        ; Initialize counter to 0

.loop:
    test rdi, rdi       ; Check if current node is NULL
    jz .return          ; If NULL, we're at the end of the list
    inc rax             ; Increment counter
    mov rdi, [rdi + 8]  ; Move to next node (node->next)
    jmp .loop           ; Repeat

.return:
    ret 