/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#include <fstream>
#include <iostream>
#include <regex>
#include <sys/shm.h>
#include <sys/sem.h>
#include "ParserSlave.hpp"

plz::ParserSlave::ParserSlave(const Task &task) : _task(task)
{
	std::ifstream t(task.filename);
	if (!t.good())
		throw std::runtime_error("Couldn't open file '" + std::string(_task.filename) + "'");
	_fileContent = std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	switch (_task.information) {
	case PHONE_NUMBER:
		_regex = std::regex(R"(0[0-9][ ]?[0-9][0-9][ ]?[0-9][0-9][ ]?[0-9][0-9][ ]?[0-9][0-9])");
		break;
	case EMAIL_ADDRESS:
		_regex = std::regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4})");
		break;
	case IP_ADDRESS:
		_regex = std::regex(
			R"((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))");
		break;
	}
	_semaphoreIndex = semget(42, 1, SHM_R | SHM_W);
	if (_semaphoreIndex == -1) {
		_semaphoreIndex = semget(42, 1, IPC_CREAT | SHM_R | SHM_W);
		semctl(_semaphoreIndex, 0, SETVAL, 1);
	}
}

std::vector<std::string> plz::ParserSlave::startJob()
{
	std::sregex_iterator iter(_fileContent.begin(), _fileContent.end(), _regex);
	for (; iter != std::sregex_iterator(); ++iter) {
		_foundItems.push_back((*iter)[0]);
		lock();
		std::cout << (*iter)[0] << std::endl;
		unlock();
	}
	return _foundItems;
}

plz::ParserSlave::~ParserSlave()
{
}

void plz::ParserSlave::lock()
{
	struct sembuf occup{};

	bzero(&occup, sizeof(struct sembuf));
	occup.sem_num = 0;
	occup.sem_flg = 0;
	occup.sem_op = -1;
	semop(_semaphoreIndex, &occup, 1);
}

void plz::ParserSlave::unlock()
{
	struct sembuf occup{};

	bzero(&occup, sizeof(struct sembuf));
	occup.sem_num = 0;
	occup.sem_flg = 0;
	occup.sem_op = 1;
	semop(_semaphoreIndex, &occup, 1);
}