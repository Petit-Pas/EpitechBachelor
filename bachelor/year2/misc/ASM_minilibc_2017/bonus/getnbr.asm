	BITS	64
	GLOBAL	getnbr

	SECTION	.text

mult_by_10:
	xor	r11, r11
	mov	r12, rax
mult_loop:
	cmp	r11, 9
	je	continue
	add	rax, r12
	inc	r11
	jmp	mult_loop
	
getnbr:
	xor	rax, rax
	mov	r13, 1
	jmp	check_negative

getnbr_loop:	
	cmp	[rdi], byte '0'
	jl	check_end
	cmp	[rdi], byte '9'
	jg	check_end
	jmp	mult_by_10
continue:
	movzx	rsi, byte [rdi]
	sub	rsi, '0'
	add	rax, rsi
	inc	rdi
	jmp	getnbr_loop

check_end:
	cmp	r13, byte -1
	jne	end
	neg	rax

end:
	ret

inc_neg:	
	inc 	rdi

check_negative:
	cmp	[rdi], byte '+'
	je	inc_neg
	cmp	[rdi], byte '-'
	jne	getnbr_loop
	neg	r13
	jmp	inc_neg
