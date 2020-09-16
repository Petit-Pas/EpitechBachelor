/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Arguments parser
*/

#ifndef ZAPPY_ARGUMENTS_PARSER_HPP
#define ZAPPY_ARGUMENTS_PARSER_HPP

#include <string>

namespace parse {
	class ArgumentsParser {
	public:
		ArgumentsParser(int ac, char **av);
		~ArgumentsParser();

		bool helpWanted(int ac, char **av) const;
		bool validArguments() const;
		int getPort() const;
		std::string getTeamName() const;
		std::string getIp() const;

	private:
		void extractPort(const std::string &port);
		void extractTeamName(const std::string &teamName);
		void extractIp(const std::string &ip);

		bool _portFlag;
		int _port;
		bool _teamNameFlag;
		std::string _teamName;
		bool _ipFlag;
		std::string _ip;
		bool _error;
	};
}

#endif //ZAPPY_ARGUMENTS_PARSER_HPP
