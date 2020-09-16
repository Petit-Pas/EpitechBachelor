//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// find origin (first player or not)
//

#include <sstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

#include <boost/algorithm/string/join.hpp>

#include <ctime>
#include <unistd.h>

#include "CmdFindOrigins.hpp"
#include "CmdBroadcast.hpp"
#include "Broadcast.hpp"

Cmd::FindOrigins::FindOrigins(const std::shared_ptr<Connection> &connection)
	: AComplexCommand(connection)
{
	findId();
	_actions.push_back(std::make_shared<Cmd::Broadcast>(_com, "NEW " + _ID));
	BROADCAST_HANDLE["NOT_FIRST"] = &Cmd::FindOrigins::notFirst;
	BROADCAST_HANDLE["NEW"] = &Cmd::FindOrigins::recvNew;
	BROADCAST_HANDLE["OTHER_NEW"] = &Cmd::FindOrigins::addPlayer;
	BROADCAST_HANDLE["LIST_PLAYERS"] = &Cmd::FindOrigins::recvListPlayers;

}

void Cmd::FindOrigins::findId()
{
	std::ostringstream ss;
	timespec time;
	auto pid = getpid();

	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 100000000);
	int rndm = dist(rd);

        clock_gettime(CLOCK_REALTIME, &time);

	ss << std::setfill('0') << std::setw(11) << time.tv_sec <<
		"s:" << std::setfill('0') << std::setw(9) << time.tv_nsec << "ns-" <<
		std::setfill('0') << std::setw(6) << pid << ";" <<
		std::setfill('0') << std::setw(9) << rndm;

	_ID += ss.str();
	_players[_ID] = false;
}

void Cmd::FindOrigins::sendListPlayers()
{
	std::vector<std::string> players;

	for (const auto &id : _players) {
		if (id.first != _ID)
			players.push_back(id.first);
	}
	std::string addition = boost::algorithm::join(players, " ");

	addition = _ID + " " + addition;
	_actions.push_back(std::make_shared<Cmd::Broadcast>(_com, "LIST_PLAYERS " + addition));
}

void Cmd::FindOrigins::updateCommands(ADrone &drone)
{
	if (drone.getTotalTicks() > 380) {
		findRealId(drone);
	}
}

bool Cmd::FindOrigins::addPlayer(const std::string &id)
{
	if (_players.find(id) == _players.end()) {
		_players[id] = false;
		return (true);
	}
	return (false);
}

void Cmd::FindOrigins::setPlayerList(const std::string &id, bool status)
{
	_players[id] = status;
}

bool Cmd::FindOrigins::notFirst(const ::Broadcast::Message &message, ADrone &drone)
{
	const auto &params = message.getParams();

	if (params.size() == 2 && _ID == params[0]) {
		std::istringstream iss(params[1]);
		std::size_t id;
		iss >> id;
		if (!iss.fail()) {
			drone.setId(id);
			_toDelete = true;
			return (true);
		}
	}
	return (false);
}

bool Cmd::FindOrigins::recvNew(const ::Broadcast::Message &message, ADrone &drone)
{
	addPlayer(message, drone);
	_actions.push_back(std::make_shared<Cmd::Broadcast>(_com, "OTHER_NEW " + _ID));
	return (true);
}

bool Cmd::FindOrigins::addPlayer(const ::Broadcast::Message &message, ADrone &)
{
	addPlayer(message.getParamsLine());
	return (true);
}

void Cmd::FindOrigins::findRealId(ADrone &drone)
{
	std::vector<std::string> players;

	for (const auto &id : _players) {
		players.push_back(id.first);
	}
	std::sort(players.begin(), players.end());
	for (size_t i = 0; i < players.size(); i++) {
		if (_ID == players[i]) {
			drone.setId(i + 1);
			drone.setMaxId(players.size() + 1);
			_toDelete = true;
			break;
		}
	}
}

bool Cmd::FindOrigins::recvListPlayers(const ::Broadcast::Message &message, ADrone &drone)
{
	auto params = message.getParams();
	bool status = true;

	for (const auto &param : params)
		status = status && !addPlayer(param);

	setPlayerList(params[0], status);
	if (!status || !_players[_ID]) {
		sendListPlayers();
		_players[_ID] = true;
	} else {
		findRealId(drone);
	}
	return (true);
}

bool Cmd::FindOrigins::unusedMessage(const std::string &servMessage, ADrone &drone)
{
	if (::Broadcast::Broadcast::isMessage(servMessage)) {
		::Broadcast::Message message(servMessage);
		if (BROADCAST_HANDLE.find(message.getFunction()) != BROADCAST_HANDLE.end()) {
			auto func = BROADCAST_HANDLE.at(message.getFunction());
			return ((this->*func)(message, drone));
		}
	}
	return (false);
}
