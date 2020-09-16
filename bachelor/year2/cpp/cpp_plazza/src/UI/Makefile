##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

CXX	=	clang++

RM	=	rm -fv

SRC	=	Main.cpp			\
		MasterGUI.cpp		\
		../Core/Master.cpp			\
		../Core/MessageQueue.cpp		\
		../Core/ParserMaster.cpp		\
		../Core/ParserSlave.cpp		\
		../Core/Thread.cpp			\
		../Core/ThreadData.cpp		\
		../Core/ThreadPoolManager.cpp	\
		../UI/Window.cpp			\
		../UI/Display.cpp			\
		../UI/Widget.cpp			\
		../UI/PlotLine.cpp		\
		../../ImGui/imgui_demo.cpp		\
		../../ImGui/imgui_draw.cpp		\
		../../ImGui/imgui.cpp			\
		../../ImGui/imgui-SFML.cpp



OBJ	=	$(SRC:.cpp=.o)

NAME	=	plazza

CXXFLAGS=	-W -Wall -Wextra -pedantic -std=c++14 -g -I../../include -I../Core

LDXXFLAGS=	-lsfml-system -lsfml-graphics -lsfml-window -lGL 

all:	$(NAME)

$(NAME):$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -lpthread $(LDXXFLAGS)
	mv $(NAME) ../../

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) ../../$(NAME)

re:	fclean all
