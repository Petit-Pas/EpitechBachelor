	BITS	64
	GLOBAL	strcasecmp

	SECTION	.text

strcasecmp:
	
	xor	r11, r11
	xor	r12, r12
	xor	r13, r13

_loopstrcasecmp:
	
	movzx	r12, byte [rdi + r11] ;stores the 2 bytes to compare, in order to be able to modify them
	movzx	r13, byte [rsi + r11]

	cmp	r12, 0			;if we reach the end of 1 of the string
	je	_end
	cmp	r13, 0
	je	_end

	cmp	r12, 97		;if the first character is >= than 'a'
	jge	_first_might
_continue:
	cmp 	r13, 97		;if the second character is >= than 'a'
	jge	_second_might
_continue_second:
	cmp	r12, r13
	jne	_end
	
	inc	r11
	jmp	_loopstrcasecmp

_first_might:
	cmp	r12, 122	;if the first character is also <= 'z'
	jle	_sub_first
	jmp	_continue

_second_might:
	cmp	r13, 122	;if the first character is also <= 'z'
	jle	_sub_second
	jmp	_continue_second

_sub_first:
	sub	r12, 32		;modify the character to put it in capital letter 
	jmp	_continue

_sub_second:
	sub	r13, 32		;modify the character to put it in capital letter 
	jmp	_continue_second
	
_end:
	movzx	r12, byte [rdi + r11] ;remove to keep the false return value of true strcasecmp
	movzx	r13, byte [rsi + r11] ;remove to keep the false return value of true strcasecmp
	sub	r12, r13
	mov	rax, r12
	ret
