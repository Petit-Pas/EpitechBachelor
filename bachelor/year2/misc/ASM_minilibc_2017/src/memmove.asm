	BITS	64
	GLOBAL	memmove

	SECTION	.text

memmove:

	mov	r12, rdi	;check if we have to do the move in reverse 
	sub 	r12, rsi
	cmp	r12, 0
	jge	_right	

_left:
	xor 	r12,r12

_loop_left:
	cmp	r12, rdx	;as long as we don't reach the end of the wanted size
	je	_end

	mov	al, byte [rsi, + r12] ;stores the byte to copy
	mov	byte [rdi + r12], al  ;put the stored byte in the buffer to fill

	inc 	r12
	jmp	_loop_left

_right:	
	dec	rdx
	
_loop_right:
	cmp	rdx, 0 	;as long as we don't reach the beggining of the buffer (as doing it in reverse)
	jl	_end

	mov	al, byte [rsi + rdx] ;stores the byte to copy
	mov	byte [rdi + rdx], al ;put the stored byte in the buffer to fill

	dec	rdx
	jmp	_loop_right
	
_end:
	mov	rax, rdi	;returns the correct pointer
	ret
