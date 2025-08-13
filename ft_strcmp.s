section .text

global ft_strcmp

ft_strcmp:
	.loop:
		mov al, [rdi]	; need to stock one of the registers string content because we cannot compare memory to memory 
		cmp al, [rsi]
		jne .end

		test al, al		; perform AND and raise flags accordingly (no need to compare it to [rsi], as they're different)
		je .end

		inc rdi
		inc rsi
		jmp .loop

	.end:
		sub al, [rsi]	; sustract rsi to al and store the result into al
		movsx rax, al	; move al to rax but keep to correct value instead of copying from 1 byte to 4 byte (like a cast)
		ret