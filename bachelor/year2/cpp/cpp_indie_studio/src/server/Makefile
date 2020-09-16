##
## EPITECH PROJECT, 2018
##
## File description:
##
##

RM	=	rm -fv

CXX	=	clang++

SRC	=	Main.cpp                                            		\
	        GameManager.cpp                                     		\
	        MapGenerator.cpp                                    		\
	        MyGlobal.cpp                                        		\
	        ServerPackageReceiver.cpp                           		\
	        ServerPackageSender.cpp                             		\
	        TimerManager.cpp						\
		../shared/network/GameServer.cpp                        	\
	        ../shared/network/TCP.cpp                               	\
	        ../shared/network/Server.cpp                               	\
	        entities/ABonus.cpp                       			\
	        entities/AEntity.cpp                      			\
	        entities/AMovable.cpp                     			\
	        entities/Bomb.cpp                         			\
	        entities/BombUp.cpp                       			\
	        entities/Breakable.cpp                    			\
	        entities/EntityFactory.cpp                			\
	        entities/Fire.cpp                         			\
	        entities/FireUp.cpp                       			\
	        entities/Player.cpp                       			\
	        entities/RandomBonusGenerator.cpp         			\
	        entities/SpeedUp.cpp                      			\
	        entities/Wall.cpp                         			\
	        entities/PassThrough.cpp                  			\
	        entities/BonusBigBomb.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	indie_studio_server

CXXFLAGS= -isystem /usr/include/irrlicht -std=c++14 -W -Wall -Wextra -g -I. -Ientities -I../shared/network -I../shared/types

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
