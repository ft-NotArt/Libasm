section .text

extern __errno_location

global ft_write

ft_write:
	mov rax, 1			; 1 is the syscall for write
	syscall				; as rax is equal to one, calls write (arguments are already placed in rdi, rsi, rdx)

	cmp rax, 0			; check return value of write
	jl .error			; jump to .error if rax is less than 0

	ret					; write syscall sets rax to correct value on its own

	.error:
		neg rax			; invert its value (pass it back to positive)
		
		mov rdi, rax	; save return value of write
		call __errno_location

		mov [rax], rdi	; write correct errno value to errno location

		mov rax, -1		; write returns -1 on error

		ret