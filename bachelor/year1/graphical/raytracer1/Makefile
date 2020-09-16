##
## Makefile for raytacer1 in /home/angevil124/prog/graphical/bsraytracer1/src
## 
## Made by Benoit
## Login   <benoit.hoffman@epitech.eu>
## 
## Started on  Fri Feb 17 14:38:35 2017 Benoit
## Last update Sat Mar 18 09:18:43 2017 Benoit
##

CC	=	gcc

SRC	=	./true_src/main.c		\
		./true_src/calc_dir_vector.c	\
		./true_src/check_light.c	\
		./true_src/check_pixel.c	\
		./true_src/do_transformations.c	\
		./true_src/plane.c		\
		./true_src/light.c		\
		./true_src/main_bis.c		\
		./true_src/my_put_pixel.c	\
		./true_src/normalise_vector.c	\
		./true_src/sphere.c		\
		./true_src/vector.c		\
		./true_src/cylinder.c		\
		./true_src/cone.c		\
		./true_src/rotate.c		\
		./true_src/parser.c		\
		./true_src/get_next_line.c	\
		./true_src/my_get_nbr.c		\
		./true_src/parser_bis.c		\
		./true_src/check_env.c		\
		./true_src/basic_print.c

OBJ	=	$(SRC:.c=.o)

NAME	=	raytracer1

LD_LIBRARY	=	-lm -lcsfml-graphics -lcsfml-window

RM	=	rm -fv

all:	$(NAME)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LD_LIBRARY)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
