##
## Makefile for Makefile in /home/Angevil/delivery/CPE_2016_Pushswap
## 
## Made by Benoît Hoffman
## Login   <Angevil@epitech.net>
## 
## Started on  Fri Nov 18 09:45:37 2016 Benoît Hoffman
## Last update Wed Nov 23 10:39:06 2016 Benoît Hoffman
##

SRC	=	main.c			\
		my_put_nbr.c		\
		reversed_rotate.c	\
		swap_list.c		\
		my_getnbr.c		\
		my_show_list.c		\
		rotate_list.c		\
		my_print.c		\
		push_and_pop.c		\
		check.c			\
		sort.c			\
		error.c			\
		new_buffer.c

OBJ	=	$(SRC:.c=.o)

NAME	=	push_swap

all:	$(NAME)

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
