LIBNAME 	= 	lib_arcade_ncurses.so

CXX 		= 	clang++

SRC 		= 	./NCursesDisplay.cpp  		\
                ../../src/Map.cpp

CXXFLAGS 	= 	-Wall -Wextra -W -I. -I../../src -std=c++11

LDXXFLAGS	=	-lmenu -lncurses

OBJ 		= 	$(SRC:.cpp=.o)

RM 			=	 rm -f

all: $(LIBNAME)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) -fpic

$(LIBNAME): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) -shared $(LDXXFLAGS)
	mv $(LIBNAME) ../
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../$(LIBNAME)
re: fclean all
