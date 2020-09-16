	BITS	64
	GLOBAL	_strcasecmp

	SECTION	.text

_strcasecmp:
	
	xor	r11, r11
	xor	r12, r12
	xor	r13, r13

_loopstrcasecmp:
	
	movzx	r12, byte [rdi + r11]
	movzx	r13, byte [rsi + r11]

	cmp	r12, 0
	je	_end
	cmp	r13, 0
	je	_end

	cmp	r12, 97
	jge	_first_might
_continue:
	cmp 	r13, 97
	jge	_second_might
_continue_second:
	cmp	r12, r13
	jne	_end
	
	inc	r11
	jmp	_loopstrcasecmp

_first_might:
	cmp	r12, 122
	jle	_sub_first
	jmp	_continue

_second_might:
	cmp	r13, 122
	jle	_sub_second
	jmp	_continue_second

_sub_first:
	sub	r12, 32
	jmp	_continue

_sub_second:
	sub	r13, 32
	jmp	_continue_second
	
_end:
	movzx	r12, byte [rdi + r11] ;remove to keep the false return value of true strcasecmp
	movzx	r13, byte [rsi + r11] ;remove to keep the false return value of true strcasecmp
	sub	r12, r13
	mov	rax, r12
	ret
