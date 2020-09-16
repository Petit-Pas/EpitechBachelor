//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// parsing
//

#include <stdexcept>
#include <cstring>
#include <iostream>
#include "Parsing.hpp"

const std::string Parsing::DEFAULT_IP =	"127.0.0.1";

void Parsing::helpPrint(char *binary)
{
	std::cout << binary << " [-i server_ip] [-p server_port]" << std::endl;
	std::cout << "default server port : " << DEFAULT_PORT << std::endl;
	std::cout << "default server ip : " << DEFAULT_IP << std::endl;
}

bool Parsing::parse(char **av, std::string &ip, int &port)
{
	port = DEFAULT_PORT;
	ip = DEFAULT_IP;
	for (size_t i = 1; av[i] != NULL; i++) {
		if (strcmp(av[i], "-h") == 0) {
			helpPrint(av[0]);
			return (true);
		} else if (strcmp(av[i], "-p") == 0) {
			if (av[i + 1] == NULL)
				throw std::runtime_error("bad argument");
			port = atoi(av[i + 1]);
			i++;
		} else if (strcmp(av[i], "-i") == 0) {
			if (av[i + 1] == NULL)
				throw std::runtime_error("bad argument");
			ip = std::string(av[i + 1]);
			i++;
		} else {
			throw std::runtime_error("bad argument");
		}
	}
	return (false);
}
