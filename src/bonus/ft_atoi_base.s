; Helper function to get the value of a character in a given base.
; input: dl = character to find, rsi = base string
; output: rax = value (index) if found, -1 if not found.
; clobbers: rcx
_get_value:
    ; to lower
    cmp dl, 'A'
    jl .to_lower_done
    cmp dl, 'Z'
    jg .to_lower_done
    add dl, 32
.to_lower_done:
    xor rax, rax            ; value = 0
.loop:
    mov cl, byte [rsi + rax]
    test cl, cl             ; end of base string?
    jz .not_found
    cmp dl, cl              ; is it the char we are looking for?
    je .found
    inc rax
    jmp .loop
.found:
    ret
.not_found:
    mov rax, -1
    ret

; Helper function to validate the base.
; input: rsi = base string
; output: rax = base length if valid, 0 if invalid.
; clobbers: rcx, rdx, r8, r9
_validate_base:
    xor rcx, rcx
.strlen_loop:
    mov dl, byte [rsi + rcx]
    test dl, dl
    jz .strlen_done
    cmp dl, '+'
    je .invalid
    cmp dl, '-'
    je .invalid
    cmp dl, ' '
    je .invalid
    cmp dl, '\t'
    je .invalid
    inc rcx
    jmp .strlen_loop
.strlen_done:
    cmp rcx, 1
    jle .invalid
    mov r8, rcx
    xor rcx, rcx
.outer_loop:
    cmp rcx, r8
    jge .valid
    mov r9, rcx
    inc r9
    mov dl, byte [rsi + rcx]
.inner_loop:
    cmp r9, r8
    jge .next_outer
    cmp dl, byte [rsi + r9]
    je .invalid
    inc r9
    jmp .inner_loop
.next_outer:
    inc rcx
    jmp .outer_loop
.valid:
    mov rax, r8
    ret
.invalid:
    xor rax, rax
    ret

global ft_atoi_base
section .text
ft_atoi_base:
    push rbx
    push r12
    push r13

    test rsi, rsi
    jz .return_zero
    call _validate_base
    test rax, rax
    jz .return_zero
    mov rbx, rax            ; rbx = base_len

    mov r12, rdi            ; r12 = current pointer in str
.skip_whitespace:
    mov cl, byte [r12]
    cmp cl, ' '
    je .increment_ptr
    cmp cl, '\t'
    je .increment_ptr
    jmp .handle_sign
.increment_ptr:
    inc r12
    jmp .skip_whitespace

.handle_sign:
    mov r13d, 1             ; r13d = sign (1 for positive)
    mov cl, byte [r12]
    cmp cl, '-'
    je .set_neg
    cmp cl, '+'
    je .skip_sign
    jmp .convert_loop
.set_neg:
    mov r13d, -1
.skip_sign:
    inc r12

.convert_loop:
    xor rax, rax
.main_loop:
    mov dl, byte [r12]
    push rax
    push r12
    push rsi
    call _get_value
    pop rsi
    pop r12
    pop r10
    cmp rax, -1
    je .done
    
    imul r10, rbx
    add r10, rax
    mov rax, r10
    
    inc r12
    jmp .main_loop

.done:
    imul r10, r13
    mov rax, r10
    jmp .return

.return_zero:
    xor rax, rax

.return:
    pop r13
    pop r12
    pop rbx
    ret 