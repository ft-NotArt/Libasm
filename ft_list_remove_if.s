section .text

extern free
extern ft_list_size

global ft_list_remove_if

;typedef struct s_list
;{
;void *data;
;struct s_list *next;
;} t_list;

; r12 = prev
; r13 = node

ft_list_remove_if:		; void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *)) ; (*cmp)(list_ptr->data, data_ref) ; (*free_fct)(list_ptr->data) ;
	push r12
	push r13
	push r15

	xor r12, r12
	mov r13, [rdi]
	.compare:
		cmp r13, 0
		je .end

		push rdi
		push rsi
		push rdx
		push rcx

		mov rax, rdx	; mov function pointer in rax, so we're able to call it with it's args
		mov rdi, [r13]

		sub rsp, 8		; stack alignment
		call rax
		add rsp, 8

		pop rcx
		pop rdx
		pop rsi
		pop rdi

		mov r15, r13	; save current to remove it after inc_cur

		cmp eax, 0
		je .inc_cur		; skip inc_prev if no remove to do
	.inc_prev:
		mov r12, r13
	.inc_cur:
		mov r13, [r13 + 8]
		cmp eax, 0
		jne .compare
	.remove:
		cmp r12, 0
		je .set_head
		.link_nodes:
			mov [r12 + 8], r13
			jmp .free
		.set_head:		; if on the 1st node, move head
			mov [rdi], r13
		.free:			; the actual free operations
			push rdi
			push rsi
			push rdx
			push rcx

			mov rax, rcx	; mov function pointer in rax, so we're able to call it with it's args
			mov rdi, [r15]

			sub rsp, 8		; stack alignment
			call rax
			mov rdi, r15
			call free
			add rsp, 8

			pop rcx
			pop rdx
			pop rsi
			pop rdi

		jmp .compare
	.end:
		pop r15
		pop r13
		pop r12
		ret
