bits 64

%define LIST_DATA_OFFSET 0
%define LIST_NEXT_OFFSET 8

global ft_list_remove_if
extern free

section .text
; void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
; rdi = begin_list, rsi = data_ref, rdx = cmp, rcx = free_fct
ft_list_remove_if:
  ; Check if begin_list pointer is NULL
  test rdi, rdi
  jz .end
  ; Check if comparison function is NULL
  test rdx, rdx
  jz .end
  
  ; Save callee-saved registers
  push r8
  push r9
  mov r8, [rdi]      ; current = *begin_list (start with first element)
  xor r9, r9         ; previous = NULL (no previous element initially)
  jmp .loop

.loop:
  ; Check if we've reached the end of the list
  test r8, r8
  jz .end_loop
  
  ; Call comparison function: cmp(current->data, data_ref)
  ; Save all registers before function call
  push rdi
  push rsi
  push rdx
  push rcx
  push r8
  push r9
  mov rdi, [r8 + LIST_DATA_OFFSET]  ; Load current node's data
  call rdx                          ; Call comparison function
  ; Restore all registers after function call
  pop r9
  pop r8
  pop rcx
  pop rdx
  pop rsi
  pop rdi
  
  ; Check comparison result: if 0, elements match (remove node)
  test rax, rax
  jz .remove_node
  jnz .next_node

.remove_node:
  ; Check if this is the first node (no previous node)
  test r9, r9
  jnz .link_previous_to_next
  jmp .link_to_next

.link_previous_to_next:
  ; Not first node: link previous->next = current->next
  mov rax, [r8 + LIST_NEXT_OFFSET]  ; Get current->next
  mov [r9 + LIST_NEXT_OFFSET], rax  ; Set previous->next = current->next
  jmp .free_node

.link_to_next:
  ; First node: update *begin_list = current->next
  mov rax, [r8 + LIST_NEXT_OFFSET]  ; Get current->next
  mov [rdi], rax                    ; Set *begin_list = current->next
  jmp .free_node

.free_node:
  ; Check if custom free function is provided
  test rcx, rcx
  jnz .call_free_fct
  
  ; No custom free function: just free the node
  push rdi
  push rsi
  push rdx
  push rcx
  push r8
  push r9
  mov rdi, r8                       ; Pass node pointer to free
  call free wrt ..plt               ; Call standard free function
  pop r9
  pop r8
  pop rcx
  pop rdx
  pop rsi
  pop rdi
  jmp .update_current_after_free

.call_free_fct:
  ; Custom free function provided: free data first, then node
  push rdi
  push rsi
  push rdx
  push rcx
  push r8
  push r9
  mov rdi, [r8 + LIST_DATA_OFFSET]  ; Pass node->data to custom free function
  call rcx                          ; Call custom free function
  pop r9
  pop r8
  push r8
  push r9
  mov rdi, r8                       ; Pass node pointer to free
  call free wrt ..plt               ; Call standard free function
  pop r9
  pop r8
  pop rcx
  pop rdx
  pop rsi
  pop rdi
  jmp .update_current_after_free

.update_current_after_free:
  ; Update current pointer after node removal
  test r9, r9                       ; Check if there was a previous node
  jnz .link_current_to_previous_next
  mov r8, [rdi]                     ; No previous: current = *begin_list
  jmp .loop

.link_current_to_previous_next:
  mov r8, [r9 + LIST_NEXT_OFFSET]   ; Yes previous: current = previous->next
  jmp .loop

.next_node:
  ; Elements don't match: move to next node
  mov r9, r8                        ; previous = current
  mov r8, [r8 + LIST_NEXT_OFFSET]   ; current = current->next
  jmp .loop

.end_loop:
  ; Restore callee-saved registers and return
  pop r9
  pop r8
  ret

.end:
  ret 