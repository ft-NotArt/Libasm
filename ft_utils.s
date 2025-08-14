section .text

extern __errno_location

global ft_set_errno

; expect to have negative errno value in rdi - syscalls put this value in rax upon failure
ft_set_errno:
	neg rdi			; invert its value (pass it back to positive)
	call __errno_location
	mov [rax], rdi	; write correct errno value to errno location

	ret