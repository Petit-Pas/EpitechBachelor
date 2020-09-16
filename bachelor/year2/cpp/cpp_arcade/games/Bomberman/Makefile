LIBNAME 	= 	lib_arcade_bomberman.so

CXX 		= 	clang++

SRC			= 	Bomberman.cpp 			\
		                Bomb.cpp                	\
				../../src/Map.cpp		\
				Mob.cpp

CXXFLAGS 	= 	-Wall -Wextra -W -I. -I../../src -std=c++11

OBJ		 	=	$(SRC:.cpp=.o)

RM			= 	rm -f

all: $(LIBNAME)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) -fpic

$(LIBNAME): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) -shared
	mv $(LIBNAME) ../
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../$(LIBNAME)

re: fclean all
