##
## Makefile for opti in /home/shintaro/Work/Epitech/delivery/dante/opti
## 
## Made by Thomas GRANDJEAN
## Login   <thomas.grandjean@epitech.eu>
## 
## Started on  Sat May 13 13:14:10 2017 Thomas GRANDJEAN
## Last update Sat May 13 13:20:29 2017 Thomas GRANDJEAN
##

SRCS	= src/basic_print.c 	\
	  src/basic_str.c 	\
	  src/get_input.c 	\
	  src/get_map.c 	\
	  src/main.c

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
