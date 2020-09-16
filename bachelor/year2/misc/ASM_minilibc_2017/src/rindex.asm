	BITS	64
	GLOBAL	rindex

	SECTION	.text

rindex:
	xor	rax, rax
_rindex_loop:


	cmp	[rdi], byte 0	;check if '\0' is reached
	je	_check_end
	
	cmp	[rdi], sil	;we found the wanted character
	je	_set_value

_continue:	
	inc	rdi
	jmp	_rindex_loop

_set_value:
	mov 	rax, rdi	;stores the last occurence of the character
	jmp	_continue

_check_end:
	cmp	sil, 0	
	je	_set
	jmp	_end

_set:	
	mov	rax, rdi	;sets the found pointer in rax to return
	
_end:
	
	ret
