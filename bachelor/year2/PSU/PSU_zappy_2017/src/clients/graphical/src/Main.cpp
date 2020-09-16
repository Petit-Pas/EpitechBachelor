/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <iostream>
#include <random>
#include "Connection.hpp"
#include "Interface.hpp"

#define ASKHELP(s) ((s) == "-h" || (s) == "--help")

int help(bool err)
{
	int ret = err ? 1 : 0;
	std::ostream out((err ? std::cerr.rdbuf() : std::cout.rdbuf()));

	out << "USAGE" << std::endl;
	out << "\t\t./spectate IP PORT\n" << std::endl;
	out << "DEFINITION" << std::endl;
	out << "\t\tIP\tServer's ip address" << std::endl;
	out << "\t\tPORT\tServer's listening port" << std::endl;
	return ret;
}

int main(int ac, char **av)
{
	if (ac != 3)
		return help(!(ac == 2 && ASKHELP(std::string(av[1]))));

	srand(getpid());
	try {
		Interface interface(std::string(av[1]), atoi(av[2]));
		interface.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 84;
	}

	return 0;
}