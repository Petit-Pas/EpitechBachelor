/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include <iostream>
#include "MenuClient.hpp"
#include "Parsing.hpp"

int main(int, char **av)
{
	try {
		int port;
		std::string ip;

		if (Parsing::parse(av, ip, port)) {
			return (0);
		}
		MenuClient client(ip, port);
	} catch (std::runtime_error err) {
		std::cerr << err.what() << std::endl;
		return (84);
	}
	return (0);
}
