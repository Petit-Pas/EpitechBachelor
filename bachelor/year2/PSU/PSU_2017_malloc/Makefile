LIBNAME = libmy_malloc.so
CC = gcc

SRC = 		src/malloc.c 		\
		    src/blocks_tools.c 	\
		    src/tools_print.c   \
		    src/main_tools.c

CFLAGS = -Wall -Wextra -W -Iinclude
OBJ = $(SRC:.c=.o)
RM = rm -f
all: $(LIBNAME)
#compilation
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -fpic -pthread

#linkage
$(LIBNAME): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -shared
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBNAME)
re: fclean all
