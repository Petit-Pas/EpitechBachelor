##
## Makefile for minishell1 in /home/angevil124/prog/PSU/PSU_2016_minishell1
## 
## Made by benoit
## Login   <benoit.hoffman@epitech.eu>
## 
## Started on  Fri Jan  6 13:21:11 2017 benoit
## Last update Tue Apr 25 09:35:48 2017 Benoit Hoffman
##

SRC	=	./src/tools/get_next_line.c		\
		./src/main/main.c			\
		./src/tools/match.c			\
		./src/tools/basic.c			\
		./src/builtins/do_env.c			\
		./src/builtins/unsetenv.c		\
		./src/checks/is_in_path.c		\
		./src/builtins/new_cd.c			\
		./src/builtins/do_cd.c			\
		./src/builtins/exit.c			\
		./src/builtins/check_setenv_validity.c	\
		./src/parser/my_giant_parser.c		\
		./src/exec/exec.c			\
		./src/tools/purify_str1.c		\
		./src/tools/purify_str2.c		\
		./src/checks/my_check.c			\
		./src/tools/basic_free.c		\
		./src/tools/basic_print.c		\
		./src/parser/str_to_wordtab_pipe.c	\
		./src/parser/str_to_wordtab_quote.c	\
		./src/parser/str_to_wordtab_new.c	\
		./src/checks/check_exists.c		\
		./src/checks/is_mine.c			\
		./src/checks/perm_and_ambi.c		\
		./src/checks/check_status.c		\
		./src/exec/set_pipes.c			\
		./src/tools/my_strcmp.c			\
		./src/parser/get_separators.c		\
		./src/exec/fct_forked.c			\
		./src/parser/swap.c			\
		./src/exec/wait_all.c			\
		./src/checks/input_output.c

RM	=	rm -f

CC	=	gcc

OBJ	=	$(SRC:.c=.o)

DEBUG	?=	0

CFLAGS	+=	-I ./include/ -W -Wall -Wextra

ifeq ($(DEBUG), 1)
CFLAGS	+=	-g
endif

NAME	=	mysh

all:	$(NAME)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	re all clean fclean
