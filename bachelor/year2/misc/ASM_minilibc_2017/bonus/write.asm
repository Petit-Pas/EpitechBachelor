	BITS	64
	GLOBAL	write

	SECTION	.text

write:
	mov	rax, 1
	syscall
	ret
