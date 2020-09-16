	BITS	64
	GLOBAL	strstr

	SECTION	.text

strstr:
	xor	r11, r11
	mov	rax, rdi

	cmp	[rsi], byte 0
	je	_found
_main_loop:
	cmp	[rdi + r11], byte 0
	je	_end

	jmp	_search

_continue:	
	inc	r11
	jmp	_main_loop

_search:
	xor	r12, r12
	mov	r13, r11
	xor	r14, r14
	
_search_loop:
	cmp	[rsi + r12], byte 0
	je	_found
	
	cmp	[rdi + r13], byte 0
	je	_end

	movzx	r14, byte [rsi + r12]
	
	cmp	byte [rdi + r13], r14b
	jne	_continue

	inc	r12
	inc	r13
	jmp	_search_loop

_found:
	mov	rax, rdi
	add	rax, r11
	ret
	
_end:
	xor	rax, rax
	ret
