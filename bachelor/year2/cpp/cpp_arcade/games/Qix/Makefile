LIBNAME 	= 	lib_arcade_qix.so

CXX 		= 	clang++

SRC			= 	Qix.cpp		\
				Spark.cpp	\
				Monster.cpp	\
				Flame.cpp	\
		                ../../src/Map.cpp

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
