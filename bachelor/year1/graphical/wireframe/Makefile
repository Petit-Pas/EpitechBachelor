##
## Makefile for wireframe in /home/angevil124/prog/graphical/wireframe
## 
## Made by benoit
## Login   <benoit.hoffman@epitech.eu>
## 
## Started on  Sun Dec  4 10:41:21 2016 benoit
## Last update Sat Dec 10 13:36:22 2016 benoit
##

SRC	=	main.c				\
		my_putchar.c			\
		open.c				\
		test_window.c			\
		my_put_pixel.c			\
		my_draw_line.c			\
		my_parallel_projection.c

OBJ	=	$(SRC:.c=.o)

NAME	=	wireframe

all:	$(NAME)

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ) -lm -lcsfml-window -lcsfml-graphics

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
