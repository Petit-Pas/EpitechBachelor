//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Incantate
//

#include "CmdIncantate.hpp"

Cmd::Incantate::Incantate(const std::shared_ptr<Connection> &connection, const std::string &name)
	: SimpleCmd(connection, name, 300), _ko(false)
{
}

Cmd::Incantate::Incantate(const std::shared_ptr<Connection> &connection, bool stat, const std::string &name)
	: SimpleCmd(connection, name, 300), _ko(stat)
{
}

bool Cmd::Incantate::handleServerResponse(const std::string &serv, ADrone &drone)
{
	if (serv == "Elevation underway") {
		_ko = true;
	} else if (serv.substr(0, 13) == "Current level") {
		drone.addLevel();
		_toDelete = true;
	} else if (serv == "ko") {
		if (_ko) {
			_toDelete = true;
		} else {
			_ko = true;
		}
	} else {
		return (false);
	}
	return (true);
}
