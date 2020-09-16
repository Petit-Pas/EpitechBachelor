//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ai launcher
//

#include <iostream>
#include <stdexcept>
#include <cstring>
#include "Farmer.hpp"
#include "ArgumentsParser.hpp"

int main(int ac, char **av)
{
	parse::ArgumentsParser parser(ac, av);

	if (parser.helpWanted(ac, av))
		return (0);
	if (!parser.validArguments())
		return (84);
	try {
		Drone::Farmer drone(parser.getIp(), parser.getPort(), parser.getTeamName());
		drone.simulate();
	} catch (std::runtime_error e) {
		if (strcmp(e.what(), "Connection closed") != 0)
			std::cerr << e.what() << std::endl;
	} catch (std::invalid_argument &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
