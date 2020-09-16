##
## EPITECH PROJECT, 2018
## minilibc
## File description:
## makefile tests
##

SRC	=	./src/memcpy.asm		\
		./src/memmove.asm		\
		./src/memset.asm		\
		./src/rindex.asm		\
		./src/strcasecmp.asm		\
		./src/strchr.asm		\
		./src/strcmp.asm		\
		./src/strcspn.asm		\
		./src/strlen.asm		\
		./src/strncmp.asm		\
		./src/strpbrk.asm		\
		./src/strstr.asm		\
		./src/getnbr.asm		\
		./src/strcpy.asm		\
		./src/str_to_wordtab.asm	\
		./src/thermometer.asm

OBJ	=	$(SRC:.asm=.o)

NAME	=	test

CFLAGS	=	-Wall -Wextra -I../include -I../src

LDFLAGS	=	 -I../include -I../src 

CC	=	gcc

%.o: %.asm
	nasm -o $@ $< -f elf64

all:	$(NAME)

$(NAME):$(OBJ)
	$(CC) -c main.c
	$(CC) -o $(NAME) $(OBJ) trumain.o -no-pie $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
