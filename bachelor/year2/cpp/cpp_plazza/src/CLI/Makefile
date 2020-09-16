##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

CXX	=	clang++

RM	=	rm -fv

SRC	=	Main.cpp						\
		../Core/Master.cpp				\
		../Core/MessageQueue.cpp		\
		../Core/ParserMaster.cpp		\
		../Core/ParserSlave.cpp			\
		../Core/Thread.cpp				\
		../Core/ThreadData.cpp			\
		../Core/ThreadPoolManager.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	plazza

CXXFLAGS=	-W -Wall -Wextra -pedantic -std=c++14 -g -I../Core -ofast

all:	$(NAME)

$(NAME):$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -lpthread
	mv $(NAME) ../../

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) ../../$(NAME)

re:	fclean all
