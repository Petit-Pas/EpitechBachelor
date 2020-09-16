//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Simple Command
//

#include "SimpleCmd.hpp"

Cmd::SimpleCmd::SimpleCmd(const std::shared_ptr<Connection> &connection, const std::string &name, size_t ticks, const std::string &args) : ACommand(connection), _msg(name), _ticks(ticks)
{
	if (!args.empty()) {
		_msg += " " + args;
	}
}

bool Cmd::SimpleCmd::handleServerResponse(const std::string &str, ADrone &drone)
{
	if (!_done) {
		return (false);
	}
	if (str == "ok") {
		_toDelete = true;
		okCase(drone);
	} else if (str == "ko") {
		std::cout << "Server: KO " << std::endl;
		_toDelete = true;
		koCase(drone);
	}
	return (_toDelete);
}

bool Cmd::SimpleCmd::sendCommand(ADrone &)
{
	if (!_done) {
		_done = true;
		_com->sendMsg(_msg);
		return (true);
	}
	return (false);
}

void Cmd::SimpleCmd::update(ADrone &)
{
}

void Cmd::SimpleCmd::koCase(ADrone &)
{
}

void Cmd::SimpleCmd::okCase(ADrone &)
{
}

size_t Cmd::SimpleCmd::getTicksPassed() const
{
	return ((_toDelete) ? (_ticks) : (0));
}
