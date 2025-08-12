; Helper function to get the value of a character in a given base.
; input: dl = character to find, rsi = base string
; output: rax = value (index) if found, -1 if not found.
; clobbers: rcx
_get_value:
    ; Convert character to lowercase for case-insensitive comparison
    cmp dl, 'A'
    jl .to_lower_done
    cmp dl, 'Z'
    jg .to_lower_done
    add dl, 32              ; Convert uppercase to lowercase (ASCII difference)
.to_lower_done:
    xor rax, rax            ; Initialize value to 0 (index counter)
.loop:
    mov cl, byte [rsi + rax] ; Get current character from base string
    test cl, cl             ; Check if we reached end of base string (NULL terminator)
    jz .not_found
    cmp dl, cl              ; Compare input character with current base character
    je .found               ; If match found, return the index
    inc rax                 ; Move to next character in base string
    jmp .loop
.found:
    ret                     ; Return index (already in rax)
.not_found:
    mov rax, -1             ; Return -1 if character not found in base
    ret

; Helper function to validate the base string.
; input: rsi = base string
; output: rax = base length if valid, 0 if invalid.
; clobbers: rcx, rdx, r8, r9
_validate_base:
    xor rcx, rcx            ; Initialize length counter to 0
.strlen_loop:
    mov dl, byte [rsi + rcx] ; Get current character from base string
    test dl, dl             ; Check for end of string (NULL terminator)
    jz .strlen_done
    ; Check for invalid characters: +, -, space, tab
    cmp dl, '+'
    je .invalid
    cmp dl, '-'
    je .invalid
    cmp dl, ' '
    je .invalid
    cmp dl, '\t'
    je .invalid
    inc rcx                 ; Increment length counter
    jmp .strlen_loop
.strlen_done:
    cmp rcx, 1              ; Base must be at least 2 characters long
    jle .invalid
    mov r8, rcx             ; Save base length in r8
    xor rcx, rcx            ; Reset counter for duplicate check
.outer_loop:
    cmp rcx, r8             ; Check if we've processed all characters
    jge .valid
    mov r9, rcx
    inc r9                  ; r9 = next character index
    mov dl, byte [rsi + rcx] ; Get current character
.inner_loop:
    cmp r9, r8              ; Check if we've compared with all remaining characters
    jge .next_outer
    cmp dl, byte [rsi + r9] ; Compare current character with next character
    je .invalid             ; If duplicate found, base is invalid
    inc r9                  ; Move to next character for comparison
    jmp .inner_loop
.next_outer:
    inc rcx                 ; Move to next character in outer loop
    jmp .outer_loop
.valid:
    mov rax, r8             ; Return base length if valid
    ret
.invalid:
    xor rax, rax            ; Return 0 if base is invalid
    ret

global ft_atoi_base
section .text
ft_atoi_base:
    ; Save callee-saved registers
    push rbx
    push r12
    push r13

    ; Check if base string is NULL
    test rsi, rsi
    jz .return_zero
    ; Validate the base string
    call _validate_base
    test rax, rax           ; Check if base is valid
    jz .return_zero
    mov rbx, rax            ; Store base length in rbx

    mov r12, rdi            ; Save string pointer in r12
.skip_whitespace:
    mov cl, byte [r12]      ; Get current character
    cmp cl, ' '             ; Check for space
    je .increment_ptr
    cmp cl, '\t'            ; Check for tab
    je .increment_ptr
    jmp .handle_sign        ; If not whitespace, handle sign
.increment_ptr:
    inc r12                 ; Skip whitespace character
    jmp .skip_whitespace

.handle_sign:
    mov r13d, 1             ; Initialize sign to positive (1)
    mov cl, byte [r12]      ; Get current character
    cmp cl, '-'             ; Check for negative sign
    je .set_neg
    cmp cl, '+'             ; Check for positive sign
    je .skip_sign
    jmp .convert_loop       ; If no sign, start conversion
.set_neg:
    mov r13d, -1            ; Set sign to negative (-1)
.skip_sign:
    inc r12                 ; Skip the sign character

.convert_loop:
    xor rax, rax            ; Initialize result to 0
.main_loop:
    mov dl, byte [r12]      ; Get current character from input string
    ; Save registers before calling _get_value
    push rax                ; Save current result
    push r12                ; Save string pointer
    push rsi                ; Save base string pointer
    call _get_value         ; Get character value in base
    ; Restore registers after call
    pop rsi
    pop r12
    pop r10                 ; Restore result to r10 (was rax)
    cmp rax, -1             ; Check if character was found in base
    je .done                ; If not found, conversion is complete
    
    ; Multiply current result by base and add new digit
    imul r10, rbx           ; result = result * base_length
    add r10, rax            ; result = result + digit_value
    mov rax, r10            ; Update result
    
    inc r12                 ; Move to next character
    jmp .main_loop

.done:
    ; Apply sign to final result
    imul r10, r13           ; result = result * sign
    mov rax, r10
    jmp .return

.return_zero:
    xor rax, rax            ; Return 0 for invalid input

.return:
    ; Restore callee-saved registers
    pop r13
    pop r12
    pop rbx
    ret 