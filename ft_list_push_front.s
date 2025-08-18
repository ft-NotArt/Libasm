section .text

extern malloc

global ft_list_push_front

;typedef struct s_list
;{
;void *data;
;struct s_list *next;
;} t_list;

ft_list_push_front:		; void ft_list_push_front(t_list **begin_list, void *data) ;
	push rdi
	push rsi

	sub rsp, 8			; stack alignment

	mov rdi, 16
	call malloc

	add rsp, 8

	pop rsi
	pop rdi

	cmp rax, 0
	je .error

	mov [rax], rsi		; assign data param in our node data

	mov r10, [rdi]
	mov [rax + 8], r10	; assign previous head to our node next

	mov [rdi], rax		; update the list head

	.error:
		ret				; returns NULL (already in rax)
