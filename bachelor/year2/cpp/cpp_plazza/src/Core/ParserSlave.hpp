/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#ifndef CPP_PLAZZA_ParserSlave_HPP
# define CPP_PLAZZA_ParserSlave_HPP

#include <string>
#include <regex>
#include <vector>
#include "Plazza.hpp"

namespace plz {
	class ParserSlave {
	public:
		explicit ParserSlave(const Task &task);
		std::vector<std::string> startJob();
		virtual ~ParserSlave();
		void lock();
		void unlock();
	private:
		Task _task;
		std::regex _regex;
		std::string _fileContent;
		std::vector<std::string> _foundItems;
		int _semaphoreIndex;
	};
}

#endif //CPP_PLAZZA_ParserSlave_HPP
