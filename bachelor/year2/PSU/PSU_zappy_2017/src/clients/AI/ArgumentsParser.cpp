/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Arguments parser
*/

#include <iostream>
#include <arpa/inet.h>
#include "ArgumentsParser.hpp"

parse::ArgumentsParser::ArgumentsParser(int ac, char **av) :
	_portFlag(false), _port(-1), _teamNameFlag(false), _teamName(""),
	_ipFlag(false), _ip("127.0.0.1"), _error(false)
{
	if (ac != 5 && ac != 7)
		_error = true;
	for (int i = 0; i < ac - 1; ++i) {
		if (std::string(av[i]) == "-p")
			extractPort(std::string(av[i + 1]));
		if (std::string(av[i]) == "-n")
			extractTeamName(std::string(av[i + 1]));
		if (std::string(av[i]) == "-h")
			extractIp(std::string(av[i + 1]));
	}
}

parse::ArgumentsParser::~ArgumentsParser()
{
}

bool parse::ArgumentsParser::helpWanted(int ac, char **av) const
{
	if (ac == 2 && std::string(av[1]) == "-help") {
		std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
		std::cout << "\tport\tis the port number" << std::endl;
		std::cout << "\tname\tis the name of the team" << std::endl;
		std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
		return (true);
	}
	return (false);
}

bool parse::ArgumentsParser::validArguments() const
{
	if (_error)
		std::cerr << "You can't specify a flag more than once." << std::endl;
	if (!_portFlag || !_teamNameFlag) {
		std::cerr << "You must specify:" << std::endl;
		if (!_portFlag)
			std::cerr << "\ta port with the -p flag" << std::endl;
		if (!_teamNameFlag)
			std::cerr << "\ta team name with the -n flag" << std::endl;
	}
	return (_port != -1 && !_teamName.empty() && !_ip.empty() && !_error);
}

int parse::ArgumentsParser::getPort() const
{
	return (_port);
}

std::string parse::ArgumentsParser::getTeamName() const
{
	return (_teamName);
}

std::string parse::ArgumentsParser::getIp() const
{
	return (_ip);
}

void parse::ArgumentsParser::extractPort(const std::string &port)
{
	if (_portFlag == true)
		_error = true;
	_portFlag = true;
	if (port == "-p" || port == "-n" || port == "-h" ||
		port.find_first_not_of("1234567890") != std::string::npos ||
		std::stoi(port) > 65535)
		_port = -1;
	else
		_port = std::stoi(port);
}

void parse::ArgumentsParser::extractTeamName(const std::string &teamName)
{
	if (_teamNameFlag == true)
		_error = true;
	_teamNameFlag = true;
	if (teamName == "-p" || teamName == "-n" || teamName == "-h" || !_teamName.empty())
		_teamName = "";
	else
		_teamName = teamName;
}

void parse::ArgumentsParser::extractIp(const std::string &ip)
{
	if (_ipFlag == true)
		_error = true;
	_ipFlag = true;
	struct sockaddr_in sa;

	if (inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 1)
		_ip = "";
	else
		_ip = ip;
}