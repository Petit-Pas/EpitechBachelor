/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <sstream>
#include <strings.h>
#include <cstring>
#include "ParserMaster.hpp"

plz::ParserMaster::ParserMaster()
{
}

std::vector<plz::Task> plz::ParserMaster::parseLine(std::string toParse)
{
	_tasks.clear();
	Information type;

	std::replace(toParse.begin(), toParse.end(), ';', '\n');
	std::istringstream input;
	input.str(toParse);
	for (std::string line; std::getline(input, line);) {
		std::vector<std::string> files;
		std::istringstream lineStream;
		lineStream.str(line);
		for (std::string token; std::getline(lineStream, token, ' ');)
			files.push_back(token);
		type = getType(files.at(files.size() - 1));
		files.pop_back();
		auto tmp = createTasks(files, type);
		_tasks.insert(_tasks.end(), tmp.begin(), tmp.end());
	}
	return _tasks;
}

std::vector<plz::Task> plz::ParserMaster::createTasks(std::vector<std::string> files, plz::Information type)
{
	std::vector<Task> tasks;
	for (auto &it : files) {
		if (access(it.c_str(), F_OK) != -1) {
			Task tmp;
			bzero(tmp.filename, 256);
			strcpy(tmp.filename, it.c_str());
			tmp.information = type;
			tasks.push_back(tmp);
		}
	}
	return tasks;
}

plz::Information plz::ParserMaster::getType(std::string toParse)
{
	if (toParse == "IP_ADDRESS")
		return plz::IP_ADDRESS;
	else if (toParse == "PHONE_NUMBER")
		return plz::PHONE_NUMBER;
	else if (toParse == "EMAIL_ADDRESS")
		return plz::EMAIL_ADDRESS;
	else
		throw std::runtime_error("Invalid line ?");
}

std::string plz::ParserMaster::getNextLine()
{
	std::string line;
	fd_set s_rd;
	struct timeval timeout = {0, 100};

	FD_ZERO(&s_rd);
	FD_SET(fileno(stdin), &s_rd);
	if (select(fileno(stdin) + 1, &s_rd, nullptr, nullptr, &timeout))
		if (!std::getline(std::cin, line))
			throw std::runtime_error("EOF");
	return line;
}

std::vector<plz::Task> plz::ParserMaster::parseLine()
{
	Information type;
	std::string toParse = getNextLine();

	_tasks.clear();
	std::replace(toParse.begin(), toParse.end(), ';', '\n');
	std::istringstream input;
	input.str(toParse);
	for (std::string line; std::getline(input, line);) {
		std::vector<std::string> files;
		std::istringstream lineStream;
		lineStream.str(line);
		for (std::string token; std::getline(lineStream, token, ' ');)
			files.push_back(token);
		type = getType(files.at(files.size() - 1));
		files.pop_back();
		auto tmp = createTasks(files, type);
		_tasks.insert(_tasks.end(), tmp.begin(), tmp.end());
	}
	return _tasks;
}
