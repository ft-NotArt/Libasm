section .text

global ft_list_size

;typedef struct s_list
;{
;void *data;
;struct s_list *next;
;} t_list;

ft_list_size:			; int ft_list_size(t_list *begin_list) ;
	xor rax, rax

	.loop:
		cmp rdi, 0
		je .end

		inc rax

		mov rdi, [rdi + 8]	; hop on next node

		jmp .loop

	.end:
		ret