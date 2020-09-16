##
## Makefile for wolf3d in /home/angevil124/prog/graphical/wolf3d
## 
## Made by benoit
## Login   <benoit.hoffman@epitech.eu>
## 
## Started on  Sat Dec 17 10:34:02 2016 benoit
## Last update Fri Feb  3 13:09:39 2017 Benoit
##

SRC	=	true_src/my_putchar.c		\
		true_src/open.c			\
		true_src/main.c			\
		true_src/fill_player.c		\
		true_src/print_image.c		\
		true_src/my_draw_line.c		\
		true_src/move_forward.c		\
		true_src/raycast.c		\
		true_src/my_put_pixel.c		\
		true_src/move.c			\
		true_src/free.c			\
		true_src/sliding_walls.c	\
		true_src/put_sky_and_ground.c	\
		true_src/teleportation.c	\
		true_src/show_map.c		\
		true_src/check_end.c		\
		true_src/check_env.c		\
		true_src/solution.c		\
		true_src/map_cpy.c		\
		true_src/print_solution.c	\
		true_src/return_white.c

OBJ	=	$(SRC:.c=.o)

NAME	=	wolf3d

all:	$(NAME)

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ) -lm -lcsfml-graphics -lcsfml-window -lcsfml-audio

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
