section .text

extern ft_list_size

global ft_list_sort

;typedef struct s_list
;{
;void *data;
;struct s_list *next;
;} t_list;

; r12 = prev
; r13 = left
; r14 = right
; r15 = sorted (bool)

ft_list_sort:		; void ft_list_sort(t_list **begin_list, int (*cmp)()) ; (*cmp)(list_ptr->data, list_other_ptr->data) ;
	push r12
	push r13
	push r14
	push r15

	push rdi
	push rsi

	mov rdi, [rdi]
	call ft_list_size

	pop rsi
	pop rdi

	cmp rax, 2
	jl .end

	mov r15, 0
	.loop_start:
		cmp r15, 1		; meaning a full loop without a swap (sorted)
		je .end

		xor r12, r12
		mov r13, [rdi]
		mov r14, [r13 + 8]
		mov r15, 1		; true until we do a swap
		jmp .compare
	.set_head:
		mov [rdi], r13
	.inc:
		mov r12, r13
		mov r13, r14
		mov r14, [r14 + 8]
		cmp r14, 0
		je .loop_start
	.compare:
		push rdi
		push rsi

		mov rax, rsi	; mov function pointer in rax, so we're able to call it with it's args in rsi
		mov rdi, [r13]
		mov rsi, [r14]

		sub rsp, 8		; stack alignment
		call rax
		add rsp, 8

		pop rsi
		pop rdi

		cmp eax, 0
		jle .inc
	.swap:
		mov r15, 0			; not sorted

		mov r8, [r14 + 8]
		mov [r13 + 8], r8	; left->next = right->next

		mov [r14 + 8], r13	; right->next = left

		mov r8, r14
		mov r14, r13
		mov r13, r8			; invert left and right

		cmp r12, 0			; first 2 nodes, no prev
		je .set_head

		mov [r12 + 8], r13	; prev->next = (previous) right

		jmp .inc
	.end:
		pop r15
		pop r14
		pop r13
		pop r12
		ret


;typedef struct s_list
;{
;void *data;
;struct s_list *next;
;} t_list;

; r12 = prev
; r13 = left
; r14 = right
; r15 = sorted (bool)


; left->next = right->next
; right->next = left
; prev->next = right
; 
; 
; 
; 
; 