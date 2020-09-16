	BITS	64
	GLOBAL	counter
	GLOBAL	increase
	GLOBAL	decrease
	GLOBAL	display
	GLOBAL	add
	GLOBAL	sub
	EXTERN	printf

	SECTION	.data
format:	db "The temperature is %i", 10, 0
formatinc:	db "Increasing the temperature", 10, 0
formatdec:	db "Decreasing the temperature", 10, 0	
formatadd:	db "Adding %i to the temperature", 10, 0
formatsub:	db "Removing %i from the temperature", 10, 0

	
int:	dd 0

	SECTION	.text

counter:	
	mov	rax, [int]
	ret

	
increase:
	mov	rdi, formatinc
	call	printf
	inc	byte [int]
	ret
	
decrease:
	mov	rdi, formatdec
	call	printf
	dec	byte [int]
	ret

display:
	mov	rdi, format
	mov	rsi, [int]
	call 	printf
	ret

add:
	push	rdi
	mov	rsi, rdi
	mov	rdi, formatadd
	call 	printf
	pop	rdi
	add	[int], rdi
	ret

sub:
	push	rdi
	mov	rsi, rdi
	mov	rdi, formatsub
	call 	printf
	pop	rdi
	sub	[int], rdi
	ret
