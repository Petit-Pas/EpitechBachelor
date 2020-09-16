	BITS	64
	global	_strcpy

	section .text

_strcpy:
	xor	r11,r11		;init the counter

_loop:
	mov	al, [rsi + r11]	;al = low 8 bits (on the right), stores the char to copy
	mov	[rdi + r11], al	;store al in the dest string
	
	cmp	al,0		;check if reaches 0 in dest
	je	_end		;goes to end
	
	inc	r11		;increments counter
	jmp	_loop		;goes back to start of loop

_end:
	mov	rax, rdi	;stores dest to return it
	ret
