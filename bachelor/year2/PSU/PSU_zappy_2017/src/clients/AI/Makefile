##
## EPITECH PROJECT, 2018
## zappy
## File description:
## makefile for AI
##

CXX	=	clang++

SRC	=	ACommand.cpp	\
		Main.cpp	\
		ArgumentsParser.cpp \
		MapOperators.cpp \
		ADrone.cpp	\
		ElementMap.cpp	\
		Tile.cpp	\
		Movement.cpp	\
		Broadcast.cpp	\
		Commands/CmdConnection.cpp \
		Commands/CmdLook.cpp \
		Commands/CmdForward.cpp \
		Commands/CmdLeft.cpp \
		Commands/CmdRight.cpp \
		Commands/CmdTake.cpp \
		Commands/CmdSet.cpp \
		Commands/CmdBroadcast.cpp \
		Commands/AComplexCommand.cpp \
		Commands/SimpleCmd.cpp \
		Commands/CmdFindOrigins.cpp \
		Commands/CmdGoTo.cpp \
		Commands/CmdLevelUp.cpp \
		Commands/CmdIncantate.cpp \
		Commands/CmdInventory.cpp \
		Commands/CmdCleanTile.cpp \
		Commands/CmdJoinPeople.cpp \
		Commands/CmdSharedInventory.cpp \
		Commands/CmdMasterIncantation.cpp \
		Commands/CmdObeyIncatator.cpp \
		Drones/Farmer.cpp \
		Drones/Levels.cpp \
		../graphical/src/Connection.cpp \
		../graphical/src/Utils.cpp \
		SplitUtils.cpp

CXXFLAGS	= -Wall -Wextra -Wshadow \
		-Wuninitialized -Wunreachable-code
CXXFLAGS	+= -ICommands -I../graphical/include/ -I./ -IDrones/
CXXFLAGS	+= -std=c++14

OBJ	=	$(SRC:.cpp=.o)

NAME	=	zappy_ai

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXLIB)
	cp $(NAME) ../../../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CXXFLAGS += -g
debug: re
