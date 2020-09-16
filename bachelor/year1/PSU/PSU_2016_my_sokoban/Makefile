##
## Makefile for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
## 
## Made by benoit
## Login   <benoit.hoffman@epitech.eu>
## 
## Started on  Fri Dec  9 16:20:05 2016 benoit
## Last update Thu Dec 15 14:24:28 2016 benoit
##

SRC	=	main.c		\
		window.c	\
		strcpy.c	\
		check_move.c	\
		check_end.c	\
		copy_tab.c	\
		my_print.c	\
		manage_loop.c	\
		error.c		\
		error_open.c	\
		free.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_sokoban

all:	$(NAME)

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ) -lncurses

fclean:
	rm -f $(NAME)

clean:	fclean
	rm -f $(OBJ)

re:	clean all
