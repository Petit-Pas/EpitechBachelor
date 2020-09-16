	BITS	64
	global strchr

	section	.text

strchr:
	xor	r11, r11
_loop:
	cmp	[rdi], byte 0	;as long as we don't reach the end of the str
	je	_return_null

	cmp	[rdi], sil	;check is the wanted character is found
	je 	_return
	inc 	rdi		
	jmp	_loop

_return:
	mov	rax, rdi
	ret
	
_return_null:
	cmp	rsi, byte 0
	je	_return_last
	xor 	rax, rax	;sets return value to NULL (error case)
	ret

_return_last:
	mov	rax, rdi
	ret
