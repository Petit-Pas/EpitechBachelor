LIBNAME 	= 	lib_arcade_caca.so

CXX 		= 	clang++

SRC 		= 	./CacaDisplay.cpp		\
				Caca.cpp  				\
                ../../src/Map.cpp

CXXFLAGS 	= 	-Wall -Wextra -W -I. -I../../src -std=c++11

LDXXFLAGS	=	-lcaca

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
