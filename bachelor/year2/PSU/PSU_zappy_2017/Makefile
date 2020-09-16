##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Global Makefile
##

all:	zappy_server

zappy_server:
	make -C ./src/server

zappy_graphical:
	make -C ./src/clients/graphical

zappy_ai:
	make -C ./src/clients/AI

clean:
	make clean -C ./src/server
	make clean -C ./src/clients/graphical
	make clean -C ./src/clients/AI

fclean:  clean
	make fclean -C ./src/server
	make fclean -C ./src/clients/graphical
	make fclean -C ./src/clients/AI

re:	fclean all

reall: fclean all zappy_graphical zappy_ai

.PHONY: zappy_server zappy_graphical zappy_ai re reall all
