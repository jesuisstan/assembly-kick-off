bits 64

%define LIST_DATA_OFFSET 0
%define LIST_NEXT_OFFSET 8

global ft_list_remove_if
extern free

section .text
; void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
; rdi = begin_list, rsi = data_ref, rdx = cmp, rcx = free_fct
ft_list_remove_if:
  test rdi, rdi
  jz .end
  test rdx, rdx
  jz .end
  push r8
  push r9
  mov r8, [rdi]      ; current = *begin_list
  xor r9, r9         ; previous = NULL
  jmp .loop

.loop:
  test r8, r8
  jz .end_loop
  ; cmp(current->data, data_ref)
  push rdi
  push rsi
  push rdx
  push rcx
  push r8
  push r9
  mov rdi, [r8 + LIST_DATA_OFFSET]
  call rdx
  pop r9
  pop r8
  pop rcx
  pop rdx
  pop rsi
  pop rdi
  test rax, rax
  jz .remove_node
  jnz .next_node

.remove_node:
  test r9, r9
  jnz .link_previous_to_next
  jmp .link_to_next

.link_previous_to_next:
  mov rax, [r8 + LIST_NEXT_OFFSET]
  mov [r9 + LIST_NEXT_OFFSET], rax
  jmp .free_node

.link_to_next:
  mov rax, [r8 + LIST_NEXT_OFFSET]
  mov [rdi], rax
  jmp .free_node

.free_node:
  test rcx, rcx
  jnz .call_free_fct
  push rdi
  push rsi
  push rdx
  push rcx
  push r8
  push r9
  mov rdi, r8
  call free wrt ..plt
  pop r9
  pop r8
  pop rcx
  pop rdx
  pop rsi
  pop rdi
  jmp .update_current_after_free

.call_free_fct:
  push rdi
  push rsi
  push rdx
  push rcx
  push r8
  push r9
  mov rdi, [r8 + LIST_DATA_OFFSET]
  call rcx
  pop r9
  pop r8
  push r8
  push r9
  mov rdi, r8
  call free wrt ..plt
  pop r9
  pop r8
  pop rcx
  pop rdx
  pop rsi
  pop rdi
  jmp .update_current_after_free

.update_current_after_free:
  test r9, r9
  jnz .link_current_to_previous_next
  mov r8, [rdi]
  jmp .loop

.link_current_to_previous_next:
  mov r8, [r9 + LIST_NEXT_OFFSET]
  jmp .loop

.next_node:
  mov r9, r8
  mov r8, [r8 + LIST_NEXT_OFFSET]
  jmp .loop

.end_loop:
  pop r9
  pop r8
  ret

.end:
  ret 