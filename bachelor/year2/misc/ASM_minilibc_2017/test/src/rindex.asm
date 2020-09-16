	BITS	64
	GLOBAL	_rindex

	SECTION	.text

_rindex:
	xor	rax, rax
_rindex_loop:


	cmp	[rdi], byte 0
	je	_check_end
	
	cmp	[rdi], sil
	je	_set_value

_continue:	
	inc	rdi
	jmp	_rindex_loop

_set_value:
	mov 	rax, rdi
	jmp	_continue

_check_end:
	cmp	sil, 0
	je	_set
	jmp	_end

_set:	
	mov	rax, rdi
	
_end:
	
	ret
