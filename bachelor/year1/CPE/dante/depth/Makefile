##
## Makefile for depth in /home/shintaro/Work/Epitech/delivery/dante/depth
## 
## Made by Thomas GRANDJEAN
## Login   <thomas.grandjean@epitech.eu>
## 
## Started on  Sat May 13 12:08:14 2017 Thomas GRANDJEAN
## Last update Sat May 13 12:08:40 2017 Thomas GRANDJEAN
##

SRCS	= src/add_direction.c 		\
	  src/basic_print.c 		\
	  src/basic_str.c 		\
	  src/directional_checks.c 	\
	  src/get_input.c 		\
	  src/get_map.c 		\
	  src/main.c 			\
	  src/my_get_nbr.c 		\
	  src/print_solution.c 		\
	  src/resolve.c

OBJS	= $(SRCS:.c=.o)

NAME	= solver

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -I include

RM	= rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
