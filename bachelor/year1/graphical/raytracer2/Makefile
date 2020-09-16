##
## Makefile for raytracer2 in /home/angevil124/prog/graphical/raytracer2
## 
## Made by Benoit Hoffman
## Login   <benoit.hoffman@epitech.eu>
## 
## Started on  Tue May  9 16:22:00 2017 Benoit Hoffman
## Last update Sun May 28 17:37:34 2017 Martin Van Elslande
##

CC	=	gcc

CFLAGS	=	-Wall -Wextra -W -Iinclude -MD

LIB	=	-lcsfml-window -lcsfml-graphics -lm -pthread

RM	=	rm -f

SRC	=	./src/main_fcts/main.c				\
		./src/main_fcts/my_framebuffer_create.c 	\
		./src/main_fcts/my_put_pixel.c 			\
		./src/main_fcts/window_create.c 		\
		./src/main_fcts/ray_scene.c 			\
		./src/main_fcts/calc.c	 			\
		./src/main_fcts/struct.c 			\
		./src/main_fcts/set_struct.c 			\
		./src/main_fcts/color.c 			\
		./src/main_fcts/intersect.c 			\
		./src/main_fcts/thread.c			\
		./src/main_fcts/affichage.c			\
		./src/UTIL/is_int.c 				\
		./src/UTIL/my_getnbr.c				\
		./src/UTIL/nb_max.c 				\
		./src/mandatory/calc_dir_vector.c 		\
		./src/mandatory/sphere.c 			\
		./src/mandatory/plane.c 			\
		./src/mandatory/cylinder.c 			\
		./src/mandatory/translate.c 			\
		./src/mandatory/light.c 			\
		./src/mandatory/rotate.c 			\
		./src/mandatory/cone.c				\
		./src/parsing/adjust_values.c			\
		./src/parsing/check_args.c			\
		./src/parsing/fill_list.c			\
		./src/parsing/free_list.c			\
		./src/parsing/get_cone.c			\
		./src/parsing/get_cylinder.c			\
		./src/parsing/get_eye.c				\
		./src/parsing/get_light.c			\
		./src/parsing/get_next_line.c			\
		./src/parsing/get_plane.c			\
		./src/parsing/get_sphere.c			\
		./src/parsing/linked_list.c			\
		./src/parsing/my_number.c			\
		./src/parsing/my_string.c			\
		./src/parsing/parsing.c				\
		./src/parsing/set_reflection.c			\
		./src/parsing/usage.c				\
		./src/parsing/wordtab.c				\
		./src/main_fcts/print_buffer.c			\
		./src/main_fcts/blurring.c			\
		./src/main_fcts/colorize.c			\
		./src/main_fcts/prepare_thread.c		\
		./src/main_fcts/reflect.c			\
		./src/main_fcts/limited_obj.c			\
		./src/main_fcts/pattern.c

OBJ	=	$(SRC:.c=.o)

DEP	=	$(SRC:.c=.d)

NAME	=	raytracer2

all	:	$(NAME);

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB)

debug	:	CFLAGS += -ggdb3

debug	:	re

fast	:	CFLAGS += -O2

fast	:	re

clean	:
		$(RM) $(OBJ) $(DEP)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	=	all debug clean fclean re

-include	$(DEP)
