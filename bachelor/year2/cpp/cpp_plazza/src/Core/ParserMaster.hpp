/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#ifndef CPP_PLAZZA_PARSERMASTER_HPP
# define CPP_PLAZZA_PARSERMASTER_HPP

#include <string>
#include <vector>
#include "Plazza.hpp"

namespace plz {
	class ParserMaster {
	public:
		explicit ParserMaster();
		std::string getNextLine();
		std::vector<Task> parseLine(std::string line);
		std::vector<Task> parseLine();
	private:
		std::vector<Task> createTasks(std::vector<std::string> files, Information type);
		Information getType(std::string toParse);
		std::vector<Task> _tasks;
	};
}

#endif //CPP_PLAZZA_PARSERMASTER_HPP
