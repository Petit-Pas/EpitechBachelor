//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// parsing
//

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <string>

class Parsing
{
public:
	static bool parse(char **av, std::string &ip, int &port);
	static void helpPrint(char *);
	static const std::string DEFAULT_IP;
private:
	Parsing() = default;
	static const int DEFAULT_PORT = 4242;
};

#endif /* !PARSING_HPP_ */
