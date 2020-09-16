##
## Makefile for generator in /home/shintaro/Work/Epitech/delivery/dante/generator
## 
## Made by Thomas GRANDJEAN
## Login   <thomas.grandjean@epitech.eu>
## 
## Started on  Sat May 13 12:13:17 2017 Thomas GRANDJEAN
## Last update Sat May 13 12:13:54 2017 Thomas GRANDJEAN
##

SRCS	= src/add_list.c 		\
	  src/basic_print.c 		\
	  src/basic_str.c 		\
	  src/break_walls.c 		\
	  src/check_walls.c 		\
	  src/generator.c 		\
	  src/my_get_nbr.c 		\
	  src/unperfect.c

OBJS	= $(SRCS:.c=.o)

NAME	= generator

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
