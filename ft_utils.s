section .text

extern __errno_location

global ft_set_errno

; expect to have negative errno value in rdi - syscalls put this value in rax upon failure
ft_set_errno:
	neg rdi			; invert its value (pass it back to positive)
	call __errno_location
	mov [rax], rdi	; write correct errno value to errno location

	ret


global ft_isspace

ft_isspace:		; bool ft_isspace(char c) ;
	cmp dil, ' '
	je .is
	cmp dil, 13
	jg .is_not
	cmp dil, 9
	jl .is_not
	.is:
		mov rax, 1
		ret
	.is_not:
		xor rax, rax
		ret