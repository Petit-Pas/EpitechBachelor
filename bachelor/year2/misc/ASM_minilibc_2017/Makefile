##
## EPITECH PROJECT, 2018
## Minilibc
## File description:
## Makefile
##


NAME		=	libasm.so

DIR		=	src

SRCS		=	$(DIR)/memcpy.asm		\
			$(DIR)/memset.asm		\
			$(DIR)/memmove.asm		\
			$(DIR)/rindex.asm		\
			$(DIR)/strcasecmp.asm		\
			$(DIR)/strchr.asm		\
			$(DIR)/strcmp.asm		\
			$(DIR)/strcspn.asm		\
			$(DIR)/strlen.asm		\
			$(DIR)/strncmp.asm		\
			$(DIR)/strpbrk.asm		\
			$(DIR)/strstr.asm

ASMFLAGS	=	-f elf64

LDFLAGS		=	-shared

ASM		=	nasm

LD		=	gcc

RM		=	rm -f

OBJS		=	$(SRCS:.asm=.o)

%.o: %.asm
		@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'
		@$(ASM) -o $@ $< $(ASMFLAGS)

all:		$(NAME)

$(NAME):	$(OBJS)
		@$(LD) $(LDFLAGS) -o $(NAME) $(OBJS) -nostdlib
		@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'

clean:
		@$(RM) $(OBJS)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean:		clean
		@$(RM) $(NAME)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'

re:		fclean all

test_run:
	make re -C test
	./test/test
	make fclean -C test

.PHONY:		all clean fclean re test_run
