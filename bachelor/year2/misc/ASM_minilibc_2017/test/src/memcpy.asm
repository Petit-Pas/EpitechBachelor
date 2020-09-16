	BITS	64
	global	_memcpy	

	section .text

_memcpy:
	xor	r11,r11

_loop:
	cmp	r11,rdx		
	je	_end		

	mov	al, byte [rsi + r11]
	mov	byte [rdi + r11], al
	
	inc	r11		
	jmp	_loop		

_end:
	mov	rax, rdi
	ret
