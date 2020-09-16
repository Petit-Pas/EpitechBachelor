	BITS	64
	GLOBAL	_strpbrk

	SECTION	.text

_strpbrk:
	xor	rax, rax
_loop:
	cmp	[rdi], byte 0
	je	_end

	jmp	_search
_continue:
	inc	rdi
	jmp	_loop

_search:
	xor	r11, r11

_search_loop:
	cmp	[rsi + r11], byte 0
	je	_continue
	mov	r12b, [rsi + r11]
	cmp	[rdi], r12b
	je	_set
	inc 	r11
	jmp	_search_loop

_set:
	mov	rax, rdi

_end:
	ret
	
