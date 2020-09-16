	BITS	64
	GLOBAL	_strcspn

	SECTION	.text

_strcspn:
	xor	rax, rax
_loop:	
	cmp	[rdi], byte 0
	je	_end

	jmp	_search
	
_continue:	
	inc	rdi
	inc	rax
	jmp	_loop

_search:
	xor	r11, r11

_search_loop:
	cmp	[rsi + r11], byte 0
	je	_continue

	mov	r12, [rsi + r11]
	cmp	[rdi], r12b
	je	_end

	inc	r11
	jmp	_search_loop
	
_end:
	ret
	
	
