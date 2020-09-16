	BITS	64
	GLOBAL	_memmove

	SECTION	.text

_memmove:

	mov	r12, rdi
	sub 	r12, rsi
	cmp	r12, 0
	jge	_right	

_left:
	xor 	r12,r12

_loop_left:
	cmp	r12, rdx
	je	_end

	mov	al, byte [rsi, + r12]
	mov	byte [rdi + r12], al

	inc 	r12
	jmp	_loop_left

_right:	
	dec	rdx
	
_loop_right:
	cmp	rdx,0
	jl	_end

	mov	al, byte [rsi + rdx]
	mov	byte [rdi + rdx], al

	dec	rdx
	jmp	_loop_right
	
_end:
	mov	rax, rdi
	ret
