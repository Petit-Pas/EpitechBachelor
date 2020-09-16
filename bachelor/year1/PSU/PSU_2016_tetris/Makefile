##
## Makefile for tetris in /home/angevil124/prog/PSU/PSU_2016_tetris
## 
## Made by Benoit
## Login   <benoit.hoffman@epitech.eu>
## 
## Started on  Fri Mar 10 11:54:14 2017 Benoit
## Last update Thu Mar 16 09:02:38 2017 Benoit
##

NAME	= tetris

CC	= gcc

RM	= rm -fv

SRCS	= 	./additional_create_tetrimino.c 	\
	  	./argument_parser.c 			\
		./basic_free.c 				\
		./basic_print.c 			\
		./basic_str.c 				\
		./check.c 				\
		./check_all.c 				\
		./check_flag.c 				\
		./check_validity.c 			\
		./create_tab_shape.c 			\
		./create_tetrimino_list.c 		\
		./get_next_line.c 			\
		./init_term.c 				\
		./main.c 				\
		./check_input.c				\
		./print_unprintable.c 			\
		./match_multi_star.c 			\
		./match_single_star.c			\
		./my_get_nbr.c 				\
		./popsort.c 				\
		./check_double.c 			\
		./print_debug.c 			\
		./print_key.c 				\
		./print_colors.c			\
		./create_map.c				\
		./basic_moves.c				\
		./rotate.c				\
		./get_down_on_it.c			\
		./validate_piece.c			\
		./remove_line.c				\
		./check_tetrimino_validity.c		\
		./get_lines.c				\
		./resize_term.c				\
		./end_game.c				\
		./print_level.c				\
		./check_game_can_be_launched.c

OBJS		= 	$(SRCS:.c=.o)

DEBUG		?=	0

CFLAGS		+=	-W -Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
CFLAGS		+=	-g -ggdb3
endif

LD_LIBRARY	=	-lncurses

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LD_LIBRARY)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
