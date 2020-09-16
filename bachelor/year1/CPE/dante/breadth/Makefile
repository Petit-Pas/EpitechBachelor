##
## Makefile for breadth in /home/shintaro/Work/Epitech/delivery/dante/breadth
## 
## Made by Thomas GRANDJEAN
## Login   <thomas.grandjean@epitech.eu>
## 
## Started on  Sat May 13 11:57:25 2017 Thomas GRANDJEAN
## Last update Sat May 13 12:05:17 2017 Thomas GRANDJEAN
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
	  src/put_new_list.c 		\
	  src/resolve.c

OBJS	= $(SRCS:.c=.o)

NAME	= solver

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -Iinclude

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
