	BITS	64
	GLOBAL	strcspn

	SECTION	.text

strcspn:
	xor	rax, rax
_loop:	
	cmp	[rdi], byte 0	;as long as we don't reach the end of the string
	je	_end

	jmp	_search
	
_continue:	
	inc	rdi
	inc	rax
	jmp	_loop

_search:
	xor	r11, r11	

_search_loop:
	cmp	[rsi + r11], byte 0 ;as long as we don't reach the end of the array of tokens
	je	_continue

	mov	r12, [rsi + r11]
	cmp	[rdi], r12b	;if we found a token
	je	_end

	inc	r11
	jmp	_search_loop
	
_end:
	ret
	
	
