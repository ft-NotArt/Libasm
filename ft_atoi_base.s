section .text

extern ft_strlen
extern ft_isspace

global ft_atoi_base


check_base:		; bool check_base(char *base) ;
	push rdi
	call ft_strlen
	pop rdi

	cmp rax, 2
	jl .invalid_base
	
	dec rdi				; equivalent to starting at i = -1 and pre-incrementating
	.loop:				; each character one at once
		inc rdi
		cmp byte [rdi], 0
		je .valid_base

		mov rdx, rdi
		mov dil, byte [rdi]
		call ft_isspace
		cmp rax, 1
		je .invalid_base
		mov rdi, rdx

		cmp byte [rdi], '+'
		je .invalid_base
		cmp byte [rdi], '-'
		je .invalid_base

		mov rcx, rdi

		.incr_inter:
			inc rcx
		.iter:			; search forward for dupes
			mov dl, byte [rcx]	; forced to do so because can't `cmp mem, mem`
			cmp dl, 0
			je .loop

			cmp byte [rdi], dl
			je .invalid_base

			jmp .incr_inter
	
	.valid_base:
		mov rax, 1
		ret
	
	.invalid_base:
		xor rax, rax
		ret


find_pos:		; int find_pos(char c, char *base) ;
	xor rax, rax

	.loop:
		cmp byte [rsi], 0
		je .not_found

		cmp byte [rsi], dil
		je .ret

		inc rsi
		inc rax
		jmp .loop

	.not_found:
		mov rax, -1
		ret

	.ret:
		ret


ft_atoi_base:		; int ft_atoi_base(char *str, char *base) ;
	cmp rdi, 0
	je .error
	cmp rsi, 0
	je .error

	push rdi
	push rsi
	mov rdi, rsi
	call check_base
	pop rsi
	pop rdi
	cmp rax, 0
	je .error

	jmp .skip_spaces
	.skip_spaces_inc:
		inc rdi
	.skip_spaces:
		mov rdx, rdi
		mov dil, byte [rdi]
		call ft_isspace
		mov rdi, rdx
		cmp rax, 1
		je .skip_spaces_inc

	mov r10, 1		; sign
	jmp .sign_loop
	.reverse_sign:
		neg r10
	.inc_sign_loop:
		inc rdi
	.sign_loop:
		cmp byte [rdi], '+'
		je .inc_sign_loop
		cmp byte [rdi], '-'
		je .reverse_sign

	push rdi
	mov rdi, rsi
	call ft_strlen
	pop rdi
	mov r11, rax		; r11 = base_len
	
	xor rax, rax
	.count_loop:
		mul r11
		mov r8, rax

		push rdi
		push rsi
		mov rdi, [rdi]
		call find_pos
		pop rsi
		pop rdi

		cmp rax, -1
		je .invalid_char
		
		add rax, r8

		inc rdi
		cmp byte [rdi], 0
		jne .count_loop

	jmp .ret
	.invalid_char:
		mov rax, r8
		div r11
	.ret:
		mul r10
		ret

	.error:
		xor rax, rax
		ret