//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// look the tiles
//

#include "CmdLook.hpp"
#include "Utils.hpp"

const size_t Cmd::Look::DEFAULT_TICKS = 7;

Cmd::Look::Look(const std::shared_ptr<Connection> &connection)
	: ACommand(connection)
{
}

bool Cmd::Look::handleServerResponse(const std::string &servMessage, ADrone &drone)
{
	Position pos = drone.getPosition();
	std::pair<int, int> delta = {0, 0};
	Orientation dir = drone.getDirection();
	Orientation secondDir = dir;
	secondDir++;
	std::string msg = servMessage;

	if (!epurMsg(msg))
		return (false);
	auto lines = Utils::split(msg, ',');

	for (const auto &line : lines) {
		const auto &tile = Tile::createTile(line);
		const auto &tilePos = pos + (dir.getDir() * delta.first + secondDir.getDir() * delta.second);
		drone.setMapTile(tilePos, tile);
		drone.setMapTile(tilePos, tile, ADrone::Reality::SUPPOSED);
		delta.second++;
		if (delta.second > delta.first) {
			delta.first++;
			delta.second *= -1;
		}
	}
	_toDelete = true;
	return (true);
}

void Cmd::Look::update(ADrone &)
{
}

bool Cmd::Look::epurMsg(std::string &servMessage) const
{
	if (servMessage[0] == '[')
		servMessage.erase(0, 1);
	else
		return (false);
	if (servMessage[0] == ' ')
		servMessage.erase(0, 1);
	if (servMessage.back() == ']')
		servMessage.erase(servMessage.end() - 1);
	else
		return (false);
	if (servMessage.back() == ' ')
		servMessage.erase(servMessage.end() - 1);
	return (true);
}

bool Cmd::Look::sendCommand(ADrone &)
{
	if (!_done) {
		_com->sendMsg("Look");
		_done = true;
		return (true);
	}
	return (false);
}

size_t Cmd::Look::getTicksPassed() const
{
	return ((_toDelete) ? (DEFAULT_TICKS) : 0);
}
