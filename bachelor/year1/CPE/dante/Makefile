##
## Makefile for dante in /home/shintaro/Work/Epitech/delivery/dante
## 
## Made by Thomas GRANDJEAN
## Login   <thomas.grandjean@epitech.eu>
## 
## Started on  Sat May 13 11:33:05 2017 Thomas GRANDJEAN
## Last update Sat May 13 12:22:54 2017 Thomas GRANDJEAN
##

NAME	=	dante

all:	$(NAME)

$(NAME):
	make -C generator/
	make -C depth/
	make -C breadth/
	make -C astar/
	make -C opti/

clean:
	make clean -C generator
	make clean -C depth
	make clean -C breadth
	make clean -C astar
	make clean -C opti

fclean:
	make fclean -C generator
	make fclean -C depth
	make fclean -C breadth
	make fclean -C astar
	make fclean -C opti

re: fclean all
