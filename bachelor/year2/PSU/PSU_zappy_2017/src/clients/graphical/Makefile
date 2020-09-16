##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Graphical client's makefile
##

RM		=	rm -fv

CXX		=	clang++

SRC		=	src/Main.cpp				\
			src/Connection.cpp			\
			src/Interface.cpp			\
			src/BackEnd.cpp				\
			src/Log.cpp					\
			src/Player.cpp				\
			src/PlayerTracker.cpp		\
			imgui/src/imgui.cpp			\
			imgui/src/imgui-SFML.cpp	\
			imgui/src/imgui_draw.cpp	\
			src/Utils.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME		=	spectate


CXXFLAGS	=	-Iinclude -Iimgui/include -W -Wall -Wextra -std=c++14

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system -lGL
	cp $(NAME) ../../../

clean:
	$(RM) $(OBJ)

fclean:  clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
