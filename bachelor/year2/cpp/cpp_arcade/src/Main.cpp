/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Internal functions
*/

#include <algorithm>
#include <iostream>
#include <dirent.h>
#include <regex>
#include "CoreManager.hpp"
#include "Parser.hpp"

int main(int ac, char **av)
{
	ar::CoreManager manager;
	std::vector<std::string> gamesNames;
	std::vector<std::string> displayNames;
	ar::Parser parser(ac, av, manager, gamesNames, displayNames);
	srand(static_cast<unsigned int>(time(nullptr)));

	int parse = parser.parse();
	if (parse != 1)
		return parse;
	try {
		manager.loadAllGames(gamesNames);
		manager.loadAllDisplay(displayNames);
		manager.loadCurrentDisplay();
		manager.menu();
	} catch (std::runtime_error e) {
		std::cerr << e.what() << std::endl;
		return 84;
	}
	manager.unloadAllDisplay();
	manager.unloadAllGames();
	return 0;
}
