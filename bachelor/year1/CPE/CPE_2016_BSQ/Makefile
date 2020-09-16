##
## Makefile for Makefile in /home/angevil124/prog/CPE/CPE_2016_BSQ
## 
## Made by benoit
## Login   <benoit.hoffman@epitech.eu>
## 
## Started on  Mon Dec  5 10:10:16 2016 benoit
## Last update Wed Dec 14 10:34:37 2016 benoit
##

SRC	=	main.c					\
		open.c					\
		fs_get_number_from_first_line.c		\
		my_putchar.c				\
		find_biggest.c				\
		my_memset.c				\
		replace.c				\
		free.c

OBJ	=	$(SRC:.c=.o)

NAME	=	bsq

all:	$(NAME)

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
