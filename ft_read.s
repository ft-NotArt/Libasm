section .text

extern __errno_location

global ft_read

ft_read:
	mov rax, 0			; 0 is the syscall for read
	syscall				; as rax is equal to one, calls read (arguments are already placed in rdi, rsi, rdx)

	cmp rax, 0			; check return value of read
	jl .error			; jump to .error if rax is less than 0

	ret					; read syscall sets rax to correct value on its own

	.error:
		neg rax			; invert its value (pass it back to positive)
		
		mov rdi, rax	; save return value of read
		call __errno_location

		mov [rax], rdi	; read correct errno value to errno location

		mov rax, -1		; read returns -1 on error

		ret