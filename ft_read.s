section .text

extern ft_set_errno

global ft_read

ft_read:
	mov rax, 0			; 0 is the syscall for read
	syscall				; as rax is equal to one, calls read (arguments are already placed in rdi, rsi, rdx)

	cmp rax, 0			; check return value of read
	jl .error			; jump to .error if rax is less than 0

	ret					; read syscall sets rax to correct value on its own

	.error:
		mov rdi, rax
		call ft_set_errno

		mov rax, -1		; write returns -1 on error
		ret