	BITS 	64
	GLOBAL	str_to_wordtab
	
	SECTION	.text
	EXTERN	 malloc

str_to_wordtab:
	xor	r11, r11	;set r11 to 0 for counter
	xor	r12, r12	;set r12 to 1 for count word
	inc	r12
	
loop_count:
	cmp	[rdi + r11], byte 0 ;if at end of input string
	je	after_count

	cmp	[rdi + r11], byte 32 ;we found a blank
	je	found_sep
	
continue_loop_count:
	inc	r11
	jmp	loop_count

found_sep:
	inc	r12
	
loop_found_sep:
	cmp	r11, 0
	je	one_less_begin	;the blank was on the beginning of the string, does not count
continue_loop_found_sep:	
	inc	r11
	cmp	[rdi + r11], byte 0 ;the blanks were at the end of the string, does not count
	je	one_less_count_end
	cmp	[rdi + r11], byte 32 ;skip every consequent blank
	jne	continue_loop_count
	jmp	loop_found_sep

one_less_begin:
	dec	r12
	jmp	continue_loop_found_sep
	
one_less_count_end:
	dec	r12
	jmp	after_count

	
	
get_size_alloc:
	xor	r11, r11
	xor	r15, r15
	
loop_get_size_alloc:
	cmp	r11, r12	;increments r15 8 by 8 to get the amount of byte needed, r12 being the amount of words
	je	alloc_and_memset
	add	r15, 8
	inc	r11
	jmp	loop_get_size_alloc


alloc_and_memset:
	mov	rdi, r15
	call 	malloc
	xor 	r11, r11
loop_memset:			;reimplementation of memset
	cmp	r15, r11
	je	after_alloc_memset

	mov	[rax + r11], byte 0
	inc	r11
	jmp	loop_memset
		
after_count:	
	;; 	mov	rax, r12 that was for returning the count of words, which is good
	;; 	ret

	mov	r13, rdi	;stores the pointer on the string to be able to call malloc
	inc	r12
	jmp	get_size_alloc
		
after_alloc_memset:
	mov	rdi, r13	;rdi is the input string
	mov	r12, rax	;r12 is the newly allocated pointer
	xor	r11, r11
	jmp	skip_blanks_final ;skip consequent blanks
loop_alloc_pointers:
	mov	[r12], rdi	;at this point, [rdi] points to the start of a new word
	add	r12, 8		
	jmp	next_word

next_word:			;skips every non blanks character, and return if find '\0'
	cmp	[rdi], byte 0
	je	end
	cmp	[rdi], byte 32
	je	skip_blanks_final
	inc	rdi
	jmp	next_word

skip_blanks_final:		;skips every blank character, changing them to '\0'
	cmp	[rdi], byte 0
	je	end
	cmp	[rdi], byte 32
	jne	loop_alloc_pointers
	mov	[rdi], byte 0
	inc	rdi
	jmp	skip_blanks_final
end:	
	ret
