bits 64

%define LIST_DATA_OFFSET 0
%define LIST_NEXT_OFFSET 8

global ft_list_sort

section .text

; void ft_list_sort(t_list **head, int (*cmp)())
; rdi = head (pointer to pointer to list), rsi = cmp function
ft_list_sort:
    ; Check if head pointer is NULL
    test rdi, rdi
    jz .ft_list_sort_end
    ; Check if list is empty
    mov r8, [rdi]
    test r8, r8
    jz .ft_list_sort_end
    ; Check if list has only one element
    mov r8, [r8 + LIST_NEXT_OFFSET]
    test r8, r8
    jz .ft_list_sort_end
    
    ; Allocate stack space for middle and next_to_middle pointers
    sub rsp, 16
    ; Save function arguments
    push rdi
    push rsi
    ; Call get_middle to find the middle of the list
    mov rdi, [rdi]
    call get_middle
    ; Restore function arguments
    pop rsi
    pop rdi
    
    ; Store middle pointer on stack
    mov [rsp + 0], rax
    ; Store next_to_middle pointer on stack
    mov rax, [rax + LIST_NEXT_OFFSET]
    mov [rsp + 8], rax
    ; Break the list in half: middle->next = NULL
    mov rax, [rsp + 0]
    mov qword [rax + LIST_NEXT_OFFSET], 0

    ; Recursively sort the first half of the list
    push rdi
    push rsi
    call ft_list_sort
    pop rsi
    pop rdi

    ; Recursively sort the second half of the list
    mov r8, rsp
    add r8, 8
    push rdi
    push rsi
    mov rdi, r8
    call ft_list_sort
    pop rsi
    pop rdi

    ; Merge the two sorted halves
    mov r8, [rsp + 8]
    push rdi
    push rsi
    mov rdi, [rdi]
    mov rdx, rsi
    mov rsi, r8
    call sorted_merge
    pop rsi
    pop rdi
    ; Update the head pointer with the merged result
    mov [rdi], rax
    ; Restore stack
    add rsp, 16
    ret

.ft_list_sort_end:
    ret

; t_list* sorted_merge(t_list *left, t_list *right, int (*cmp)(void*, void*))
; rdi = left list, rsi = right list, rdx = comparison function
sorted_merge:
   ; Check if left list is empty
   test rdi, rdi
   jz .sorted_merge_ret_right
   ; Check if right list is empty
   test rsi, rsi
   jz .sorted_merge_ret_left
   
   ; Allocate stack space for result pointer
   sub rsp, 8
   mov qword [rsp + 0], 0
   
   ; Call comparison function: cmp(left->data, right->data)
   push rdi
   push rsi
   push rdx
   mov rdi, [rdi + LIST_DATA_OFFSET]
   mov rsi, [rsi + LIST_DATA_OFFSET]
   call rdx
   pop rdx
   pop rsi
   pop rdi
   
   ; Compare result: if <= 0, left element is smaller or equal
   cmp eax, 0
   jle .sorted_merge_below_or_equal
   jmp .sorted_merge_greater

; Return left list if right is empty
.sorted_merge_ret_left:
   mov rax, rdi
   ret

; Return right list if left is empty
.sorted_merge_ret_right:
   mov rax, rsi
   ret

; Left element is smaller or equal - it becomes the head
.sorted_merge_below_or_equal:
   ; Store left node as result head
   mov [rsp + 0], rdi
   ; Recursively merge rest of left list with right list
   push rdi
   push rsi
   push rdx
   mov rdi, [rdi + LIST_NEXT_OFFSET]
   call sorted_merge
   pop rdx
   pop rsi
   pop rdi
   ; Link the result to left->next
   mov r8, [rsp + 0]
   mov [r8 + LIST_NEXT_OFFSET], rax
   jmp .sorted_merge_end

; Right element is smaller - it becomes the head
.sorted_merge_greater:
   ; Store right node as result head
   mov [rsp + 0], rsi
   ; Recursively merge left list with rest of right list
   push rdi
   push rsi
   push rdx
   mov rsi, [rsi + LIST_NEXT_OFFSET]
   call sorted_merge
   pop rdx
   pop rsi
   pop rdi
   ; Link the result to right->next
   mov r8, [rsp + 0]
   mov [r8 + LIST_NEXT_OFFSET], rax
   jmp .sorted_merge_end

; Return the merged list head
.sorted_merge_end:
   mov rax, [rsp + 0]
   add rsp, 8
   ret

; t_list* get_middle(t_list *head)
; rdi = head of the list
get_middle:
   ; Check if list is empty
   test rdi, rdi
   jz .get_middle_ret_head
   jnz .get_middle_loop

; Initialize slow and fast pointers (tecnique to find the middle of the list)
.get_middle_loop:
   sub rsp, 16
   mov [rsp + 0], rdi    ; slow pointer starts at head
   mov [rsp + 8], rdi    ; fast pointer starts at head
   jmp .get_middle_loop_condition

; Check if fast pointer can move one step
.get_middle_loop_condition:
   mov r8, [rsp + 8]
   mov r8, [r8 + LIST_NEXT_OFFSET]
   test r8, r8
   jnz .get_middle_loop_condition2
   jmp .get_middle_ret_slow

; Check if fast pointer can move two steps
.get_middle_loop_condition2:
   mov r8, [r8 + LIST_NEXT_OFFSET]
   test r8, r8
   jnz .get_middle_loop_routine
   jmp .get_middle_ret_slow

; Move slow pointer by 1, fast pointer by 2
.get_middle_loop_routine:
   ; slow = slow->next
   mov r8, [rsp + 0]
   mov r8, [r8 + LIST_NEXT_OFFSET]
   mov [rsp + 0], r8
   ; fast = fast->next->next
   mov r8, [rsp + 8]
   mov r8, [r8 + LIST_NEXT_OFFSET]
   mov r8, [r8 + LIST_NEXT_OFFSET]
   mov [rsp + 8], r8
   jmp .get_middle_loop_condition

; Return head if list is empty
.get_middle_ret_head:
   mov rax, rdi
   ret

; Return slow pointer (middle of the list)
.get_middle_ret_slow:
   mov rax, [rsp + 0]
   add rsp, 16
   ret

.end:
   ret 