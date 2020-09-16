//
// EPITECH PROJECT, 2018
// zappy
// File description:
// connection command
//

#include <sstream>
#include "CmdConnection.hpp"

CmdConnection::CmdConnection(const std::shared_ptr<Connection> &com, const std::string &name) : ACommand(com), _teamName(name), _nbResponse(0)
{
}

void CmdConnection::update(ADrone &)
{
}

bool CmdConnection::handleServerResponse(const std::string &servCmd, ADrone &drone)
{
	if (servCmd == "WELCOME") {
		if (_nbResponse != 0)
			throw std::runtime_error("This is not a valid server");
	} else if (_nbResponse == 1) {
		std::stringstream stream(servCmd);
		std::size_t nbSlots;
		stream >> nbSlots;
		drone.setRemainingSlots(nbSlots);
	} else if (_nbResponse == 2) {
		std::stringstream stream(servCmd);
		std::size_t width;
		std::size_t height;
		stream >> width;
		stream >> height;
		drone.setSize(height, width);
		_toDelete = true;
		drone.connect();
	} else {
		throw std::runtime_error("This is not a valid server");
	}
	_nbResponse++;
	return (true);
}

bool CmdConnection::isDone() const
{
	return (_toDelete);
}

bool CmdConnection::sendCommand(ADrone &)
{
	if (_nbResponse == 1 && !_done) {
		_com->sendMsg(_teamName);
		_done = true;
	}
	return (false);
}

size_t CmdConnection::getTicksPassed() const
{
	return (0);
}
