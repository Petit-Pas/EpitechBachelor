	BITS	64
	global	memcpy	

	section .text

memcpy:
	xor	r11,r11		;set the counter to 0

_loop:
	cmp	r11,rdx		;loop until the size asked is reached
	je	_end		

	mov	al, byte [rsi + r11] ;stores the byte to copy
	mov	byte [rdi + r11], al ;put the stored byte in the buffer
	
	inc	r11		
	jmp	_loop		

_end:
	mov	rax, rdi	;return the pointer to the newly filled array
	ret
