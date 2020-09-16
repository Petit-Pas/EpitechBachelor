/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Internal functions
*/

#include <iostream>
#include <dirent.h>
#include <regex>
#include <fstream>
#include "Parser.hpp"

ar::Parser::~Parser()
{
}

ar::Parser::Parser(int ac, char **av, ar::CoreManager &manager, std::vector<std::string> &gamesNames,
	std::vector<std::string> &displayNames
) : _ac(ac), _av(av), _manager(manager), _gamesNames(gamesNames), _displayNames(displayNames)
{
}

int ar::Parser::getDir(const std::string &dir, std::vector<std::string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(dir.c_str())) == nullptr) {
		std::cerr << "Error(" << errno << ") opening " << dir << std::endl;
		return 84;
	}
	while ((dirp = readdir(dp)) != nullptr) {
		if (std::regex_match(std::string(dirp->d_name), std::regex("^.*\\.so$")))
			files.push_back(dir + std::string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}

void ar::Parser::printHelp(const std::string &binaryName)
{
	std::cout << "USAGE" << std::endl;
	std::cout << "\t\t" << binaryName << " lib_file" << std::endl << std::endl;
	std::cout << "DESCRIPTION" << std::endl;
	std::cout << "\t\tlib_file\tgraphical dynamic library you want to start with." << std::endl << std::endl;
	std::cout << "KEYMAP" << std::endl;
	std::cout << "\t\tUP ARROW\tMove up" << std::endl;
	std::cout << "\t\tDOWN ARROW\tMove down" << std::endl;
	std::cout << "\t\tLEFT ARROW\tMove left" << std::endl;
	std::cout << "\t\tRIGHT ARROW\tMove right" << std::endl;
	std::cout << "\t\tSPACE\t\tSpecial action depending on the game" << std::endl;
	std::cout << "\t\tENTER\t\tValidate choice in the menu" << std::endl;
	std::cout << "\t\t1\t\tPrevious game" << std::endl;
	std::cout << "\t\t2\t\tNext game" << std::endl;
	std::cout << "\t\t3\t\tPrevious graphical interface" << std::endl;
	std::cout << "\t\t4\t\tNext graphical interface" << std::endl;
	std::cout << "\t\tR\t\tRestart the game" << std::endl;
	std::cout << "\t\tP\t\tPause the game" << std::endl;
	std::cout << "\t\tM\t\tGo to menu" << std::endl;
}

int ar::Parser::parse()
{
	if (_ac != 2) {
		std::cerr << "usage: ./arcade -h | lib_file" << std::endl << "Invalid argument(s)." << std::endl;
		return 84;
	}
	if (std::string(_av[1]) == std::string("-h")) {
		printHelp(_av[0]);
		return 0;
	}
	if (getDir("./games/", _gamesNames) == 84 || getDir("./lib/", _displayNames) == 84)
		return 84;
	auto item = std::find(_displayNames.begin(), _displayNames.end(), _av[1]);
	if (item == _displayNames.end()) {
		if (!std::ifstream(_av[1]).good()) {
			std::cerr << "Could not open " << _av[1] << std::endl;
			return 84;
		}
		_displayNames.push_back(_av[1]);
	}
	item = std::find(_displayNames.begin(), _displayNames.end(), _av[1]);
	_manager.setDisplayID(static_cast<int>(std::distance(_displayNames.begin(), item)));
	return 1;
}
