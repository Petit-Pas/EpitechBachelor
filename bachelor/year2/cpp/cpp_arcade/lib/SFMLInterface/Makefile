LIBNAME 	= 	lib_arcade_sfml.so

CXX 		= 	clang++

SRC 		= 	./SFMLDisplay.cpp  			\
                ../../src/Map.cpp

CXXFLAGS 	= 	-Wall -Wextra -W -I. -I../../src -std=c++11

LDXXFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system

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
