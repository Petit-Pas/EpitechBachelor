	BITS	64

	global strcmp
	section .text

strcmp:
	xor	r11,r11			;init counter

_loop:
	movzx	r12, BYTE [rdi + r11] 	;store a char in a register
	movzx	r13, BYTE [rsi + r11]	;store a char in a register

	cmp	r12, 0
	je	_end

	cmp	r13, 0
	je	_end
	
	cmp	r12, r13		;compare 2 char stored
	jne	_end			;if difference, returns

	inc 	r11			;increments the counter

	jmp	_loop			;goes back to start of loop

_end:
	sub	r12, r13		;calculates the difference
	mov 	rax,r12			;store the difference in the return register
	ret				;returns

	
