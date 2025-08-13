section .text

global ft_strcpy
extern ft_strlen

ft_strcpy:
	push rdi ; save rdi (dest) to the stack
	
	mov rdi, rsi ; move src to 1st arg register for ft_strlen
	call ft_strlen

	mov rcx, rax ; put ft_strlen result in rcx
	inc rcx ; increment rcx once to also copy '\0'

	pop rdi ; get back dest using stack top pointer (implicitly)

	mov rax, rdi ; save dest in rax (return value)

	rep movsb ; rep repeats an operation as many times as rcx ; movsb copies [rsi] to [rdi]

	ret
