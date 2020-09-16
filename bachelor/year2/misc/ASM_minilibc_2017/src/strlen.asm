	BITS 64
	global strlen

	section .text

strlen:
	xor 	r11,r11			;sets the counter to 0

_loop:
	cmp 	BYTE [rdi + r11],0 	;check if the character at index r11 is 0
	je	_ret			;if reached 0, go to ret label
	inc	r11			;increments counter
	jmp	_loop			;goes back to start of loop
	
_ret:
	mov 	rax,r11			;stores counter in return register
	ret				;returns
