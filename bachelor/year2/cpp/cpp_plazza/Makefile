##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

all:
	make -C ./src/CLI

ui:	fclean
	make -C ./src/UI

clean:
	make clean -C ./src/UI
	make clean -C ./src/CLI

fclean:	clean
	make fclean -C ./src/UI
	make fclean -C ./src/CLI

re:	fclean all
