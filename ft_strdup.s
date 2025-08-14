section .text

global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

ft_strdup:
	push rdi		; save string address because strlen increments it
	call ft_strlen

	mov rdi, rax	; put the number of character we need to allocate in rdi
	inc rdi			; +1 for '\0'
	call malloc

	cmp rax, 0
	je	.error

	mov rdi, rax	; put the allocated memory address into 1st arg
	pop rsi			; get the string address back as 2nd arg
	call ft_strcpy

	ret				; ft_strcpy already put dest (our allocated memory address) in rax

	.error:
		pop rdi		; clean the stack
		ret			; returns NULL (already in rax)