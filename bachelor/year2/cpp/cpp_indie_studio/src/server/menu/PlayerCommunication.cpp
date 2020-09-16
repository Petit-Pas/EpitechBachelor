//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// player
//

#include "PlayerCommunication.hpp"

PlayerCommunication::PlayerCommunication(int fd) : _socket(fd), _ready(false), _skinId(0)
{
	_client = new ClientTCP(fd);
}

PlayerCommunication::PlayerCommunication(const PlayerCommunication &player) : _socket(player.getSocket()),
	_ready(player.getReady()), _skinId(player.getSkinId()), _client(player.getClient())
{
}

int PlayerCommunication::getSocket() const
{
	return (_socket);
}

void PlayerCommunication::ready(bool status)
{
	_ready = status;
}

void PlayerCommunication::setSkin(size_t id)
{
	_skinId = id;
}

bool PlayerCommunication::getReady() const
{
	return (_ready);
}

ClientTCP *PlayerCommunication::getClient() const
{
	return (_client);
}

size_t PlayerCommunication::getSkinId() const
{
	return (_skinId);
}

void PlayerCommunication::clear()
{
	delete _client;
}

bool PlayerCommunication::isOpen() const
{
	return (_client->isOpen());
}

size_t PlayerCommunication::getPlayerId() const
{
	return (_idPlayer);
}

void PlayerCommunication::setPlayerId(size_t id)
{
	_idPlayer = id;
}
