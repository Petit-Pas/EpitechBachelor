##
## EPITECH PROJECT, 2018
##
## File description:
##
##

RM	=	rm -fv

CXX	=	clang++

SRC	=	Main.cpp                                    		\
	        TaskQueue.cpp                                       	\
	        Client.cpp                                          	\
	        ClientReceiveUpdate.cpp                             	\
	        EventReceiver.cpp                                   	\
		entities/AEntityClient.cpp                		\
		../shared/network/GameClient.cpp                        \
		../shared/network/TCP.cpp 				\
		../shared/network/Client.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	indie_studio_client

CXXFLAGS= -isystem /usr/include/irrlicht -std=c++14 -W -Wall -Wextra -g -Ientities -I../shared/network -I../shared/types -I.

LDFLAGS =   -lIrrlicht -lpthread

all:	$(NAME)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

debug:	CXXFLAGS += -ggdb3
debug:	re

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all debug clean fclean re
