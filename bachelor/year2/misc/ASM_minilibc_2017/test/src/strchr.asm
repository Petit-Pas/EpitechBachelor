	BITS	64
	global _strchr

	section	.text

_strchr:
	xor	r11, r11
_loop:
	cmp	[rdi], byte 0
	je	_return_null
	
	cmp	[rdi], sil
	je 	_return
	inc 	rdi
	jmp	_loop

_return:
	mov	rax, rdi
	ret
	
_return_null:
	cmp	rsi, byte 0
	je	_return_last
	xor 	rax, rax
	ret

_return_last:
	mov	rax, rdi
	ret
