	BITS	64
	GLOBAL	read

	SECTION	.text

read:
	mov	rax, 0
	syscall
	ret
