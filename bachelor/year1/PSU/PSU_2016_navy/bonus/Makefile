##
## Makefile for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
## 
## Made by Shintaro
## Login   <thomas.grandjean@epitech.eu>
## 
## Started on  Wed Feb  1 13:43:18 2017 Shintaro
## Last update Fri Feb 10 11:42:50 2017 Benoit
##


SRC	=	additional_fill_map.c	\
		attack.c		\
		basic_free.c		\
		basic_print.c		\
		basic_str.c		\
		change_coordinates.c	\
		check_end.c		\
		connexion.c		\
		fill_map.c		\
		get_next_line.c		\
		hit.c			\
		manage_map.c		\
		morse.c			\
		my_get_nbr.c		\
		navy.c			\
		print_custom.c		\
		put_cross.c

OBJ	=	$(SRC:.c=.o)

NAME	=	navy

CFLAGS	=	-g

all:	$(NAME)

$(NAME):	$(OBJ)
			gcc -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

reset:
		reset

re: clean all
