extern printf, scanf, fflush, stdout

section .data
	fmt_integer: db '%d', 10, 0
	fmt_integer_no_line_break: db '%d ', 0
	fmt_float: db '%f', 10, 0
	fmt_float_no_line_break: db '%f ', 0
	fmt_string: db '%s', 10, 0
	fmt_string_no_line_break: db '%s', 0
	fmt_ip_integer: db '%d', 0
	fmt_ip_float: db '%lf', 0
	message_true: db 'true ', 0
	message_false: db 'false ', 0
	message_lb: db 10, 0
	message_ip_integer: db 'Input: Enter an integer value: ', 0
	message_ip_real: db 'Input: Enter a real value: ', 0
	message_ip_boolean: db 'Input: Enter a boolean value: ', 0
	message_output: db 'Output: ', 0
	buffer_integer: dd 0

section .bss

section .text
global main

main:
	push rbp
	mov rbp, rsp
	sub rsp, 48
	mov byte [rbp - 15], 1
	mov al, byte [rbp - 15]
	mov byte [rbp - 13], al
	mov word [rbp - 17], 5
	mov ax, word [rbp - 17]
	mov word [rbp - 8], ax
	mov word [rbp - 19], 9
	mov ax, word [rbp - 19]
	mov word [rbp - 10], ax
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 2], ax
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 4], ax
	mov ax, word [rbp - 4]
	imul ax, word [rbp - 10]
	mov word [rbp - 21], ax
	mov ax, word [rbp - 2]
	add ax, word [rbp - 21]
	mov word [rbp - 23], ax
	mov ax, word [rbp - 8]
	sub ax, word [rbp - 10]
	mov word [rbp - 25], ax
	mov ax, word [rbp - 25]
	imul ax, word [rbp - 4]
	mov word [rbp - 27], ax
	mov ax, word [rbp - 23]
	add ax, word [rbp - 27]
	mov word [rbp - 29], ax
	mov ax, word [rbp - 8]
	imul ax, 2
	mov word [rbp - 31], ax
	mov ax, word [rbp - 29]
	add ax, word [rbp - 31]
	mov word [rbp - 33], ax
	mov ax, word [rbp - 10]
	imul ax, word [rbp - 2]
	mov word [rbp - 35], ax
	mov ax, word [rbp - 33]
	sub ax, word [rbp - 35]
	mov word [rbp - 37], ax
	mov ax, word [rbp - 37]
	mov word [rbp - 6], ax
	mov ax, word [rbp - 6]
	cmp ax, 10
	jle __LL0__
	mov byte [rbp - 38], 1
	jmp __LL1__
__LL0__:
	mov byte [rbp - 38], 0
__LL1__:
	mov ax, word [rbp - 8]
	cmp ax, word [rbp - 10]
	jg __LL2__
	mov byte [rbp - 39], 1
	jmp __LL3__
__LL2__:
	mov byte [rbp - 39], 0
__LL3__:
	mov al, byte [rbp - 38]
	or al, byte [rbp - 39]
	mov byte [rbp - 40], al
	mov ax, word [rbp - 2]
	cmp ax, word [rbp - 4]
	jge __LL4__
	mov byte [rbp - 41], 1
	jmp __LL5__
__LL4__:
	mov byte [rbp - 41], 0
__LL5__:
	mov al, byte [rbp - 40]
	and al, byte [rbp - 41]
	mov byte [rbp - 42], al
	mov al, byte [rbp - 42]
	and al, byte [rbp - 13]
	mov byte [rbp - 43], al
	mov al, byte [rbp - 43]
	mov byte [rbp - 14], al
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 6]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	cmp byte [rbp - 13], 0
	jz __LL6__
	mov rax, message_true
	jmp __LL7__
__LL6__:
	mov rax, message_false
__LL7__:
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf

;exiting program
	xor rax, rax
	xor rsi, rsi
	xor rdi, rdi
	call fflush
	mov rax, 1
	mov rbx, 0
	int 80h
