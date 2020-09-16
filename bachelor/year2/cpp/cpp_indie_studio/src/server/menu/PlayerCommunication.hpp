//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// player
//

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <cstring>
/* for size_t */

#include "ClientTCP.hpp"

class PlayerCommunication {
public:
	PlayerCommunication(int);
	PlayerCommunication(const PlayerCommunication &);
	~PlayerCommunication() = default;

	int getSocket() const;
	void ready(bool = true);
	void setSkin(size_t id);
	void clear();

	bool isOpen() const;

	template<typename T>
	void sendData(const T &);

	template<typename T>
	bool recvData(T &, bool = false);

	bool getReady() const;
	ClientTCP *getClient() const;
	size_t getSkinId() const;
	size_t getPlayerId() const;
	void setPlayerId(size_t);
private:
	int _socket;
	bool _ready;
	size_t _skinId;
	ClientTCP *_client;
	size_t _idPlayer;
};

template<typename T>
void PlayerCommunication::sendData(const T &obj)
{
	_client->sendData(obj);
}

template<typename T>
bool PlayerCommunication::recvData(T &obj, bool blocking)
{
	return (_client->recvData(obj, blocking));
}

#endif /* !PLAYER_HPP_ */
