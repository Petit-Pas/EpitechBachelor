##
## EPITECH PROJECT, 2021
## arcade
## File description:
## Created by Benoit HOFFMAN,
##

NAME		=	arcade

SRCS		=	./src/CoreManager.cpp		\
				./src/Parser.cpp			\
				./src/Main.cpp

OBJS		=	$(SRCS:.cpp=.o)

INCLUDE		=	-Iinclude/ -Isrc/ -I

CXX     	= 	clang++

RM			=	rm -f

CXXFLAGS	=	$(INCLUDE) -W -Wall -Wextra -std=c++11

LDFLAGS		= -ldl


all:	core games graphicals

core: $(NAME)

graphicals:
	make -C lib

games:
	make -C games

$(NAME):	$(OBJS)
		$(CXX) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		make -C games clean
		make -C lib clean
		$(RM) $(OBJS)

fclean:		clean
		make -C games fclean
		make -C lib fclean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re games graphicals
