bits 64

%define LIST_DATA_OFFSET 0
%define LIST_NEXT_OFFSET 8

global ft_list_sort

section .text

; void ft_list_sort(t_list **head, int (*cmp)())
ft_list_sort:
    test rdi, rdi
    jz .ft_list_sort_end
    mov r8, [rdi]
    test r8, r8
    jz .ft_list_sort_end
    mov r8, [r8 + LIST_NEXT_OFFSET]
    test r8, r8
    jz .ft_list_sort_end
    sub rsp, 16
    push rdi
    push rsi
    mov rdi, [rdi]
    call get_middle
    pop rsi
    pop rdi
    ; middle
    mov [rsp + 0], rax
    ; next_to_middle
    mov rax, [rax + LIST_NEXT_OFFSET]
    mov [rsp + 8], rax
    ; middle->next = 0
    mov rax, [rsp + 0]
    mov qword [rax + LIST_NEXT_OFFSET], 0

    push rdi
    push rsi
    call ft_list_sort
    pop rsi
    pop rdi

    mov r8, rsp
    add r8, 8
    push rdi
    push rsi
    mov rdi, r8
    call ft_list_sort
    pop rsi
    pop rdi

    mov r8, [rsp + 8]
    push rdi
    push rsi
    mov rdi, [rdi]
    mov rdx, rsi
    mov rsi, r8
    call sorted_merge
    pop rsi
    pop rdi
    mov [rdi], rax
    add rsp, 16
    ret

.ft_list_sort_end:
    ret

; t_list* sorted_merge(t_list *left, t_list *right, int (*cmp)(void*, void*))
sorted_merge:
   test rdi, rdi
   jz .sorted_merge_ret_right
   test rsi, rsi
   jz .sorted_merge_ret_left
   sub rsp, 8
   mov qword [rsp + 0], 0
   push rdi
   push rsi
   push rdx
   mov rdi, [rdi + LIST_DATA_OFFSET]
   mov rsi, [rsi + LIST_DATA_OFFSET]
   call rdx
   pop rdx
   pop rsi
   pop rdi
   cmp eax, 0
   jle .sorted_merge_below_or_equal
   jmp .sorted_merge_greater

.sorted_merge_ret_left:
   mov rax, rdi
   ret

.sorted_merge_ret_right:
   mov rax, rsi
   ret

.sorted_merge_below_or_equal:
   mov [rsp + 0], rdi
   push rdi
   push rsi
   push rdx
   mov rdi, [rdi + LIST_NEXT_OFFSET]
   call sorted_merge
   pop rdx
   pop rsi
   pop rdi
   mov r8, [rsp + 0]
   mov [r8 + LIST_NEXT_OFFSET], rax
   jmp .sorted_merge_end

.sorted_merge_greater:
   mov [rsp + 0], rsi
   push rdi
   push rsi
   push rdx
   mov rsi, [rsi + LIST_NEXT_OFFSET]
   call sorted_merge
   pop rdx
   pop rsi
   pop rdi
   mov r8, [rsp + 0]
   mov [r8 + LIST_NEXT_OFFSET], rax
   jmp .sorted_merge_end

.sorted_merge_end:
   mov rax, [rsp + 0]
   add rsp, 8
   ret

; t_list* get_middle(t_list *head)
get_middle:
   test rdi, rdi
   jz .get_middle_ret_head
   jnz .get_middle_loop

.get_middle_loop:
   sub rsp, 16
   mov [rsp + 0], rdi
   mov [rsp + 8], rdi
   jmp .get_middle_loop_condition

.get_middle_loop_condition:
   mov r8, [rsp + 8]
   mov r8, [r8 + LIST_NEXT_OFFSET]
   test r8, r8
   jnz .get_middle_loop_condition2
   jmp .get_middle_ret_slow

.get_middle_loop_condition2:
   mov r8, [r8 + LIST_NEXT_OFFSET]
   test r8, r8
   jnz .get_middle_loop_routine
   jmp .get_middle_ret_slow

.get_middle_loop_routine:
   mov r8, [rsp + 0]
   mov r8, [r8 + LIST_NEXT_OFFSET]
   mov [rsp + 0], r8
   mov r8, [rsp + 8]
   mov r8, [r8 + LIST_NEXT_OFFSET]
   mov r8, [r8 + LIST_NEXT_OFFSET]
   mov [rsp + 8], r8
   jmp .get_middle_loop_condition

.get_middle_ret_head:
   mov rax, rdi
   ret

.get_middle_ret_slow:
   mov rax, [rsp + 0]
   add rsp, 16
   ret

.end:
   ret 