	BITS	64
	global	_memset	

	section .text

_memset:
	xor	r11,r11		;init the counter
_loop:
	
	cmp	r11, rdx
	je	_end		;goes to end

	mov	byte [rdi + r11],sil
	
	inc	r11		;increments counter
	jmp	_loop		;goes back to start of loop

_end:
	mov	rax, rdi
	ret
