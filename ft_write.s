section .text

extern ft_set_errno

global ft_write

ft_write:
	mov rax, 1			; 1 is the syscall for write
	syscall				; as rax is equal to one, calls write (arguments are already placed in rdi, rsi, rdx)

	cmp rax, 0			; check return value of write
	jl .error			; jump to .error if rax is less than 0

	ret					; write syscall sets rax to correct value on its own

	.error:
		mov rdi, rax
		call ft_set_errno

		mov rax, -1		; write returns -1 on error
		ret