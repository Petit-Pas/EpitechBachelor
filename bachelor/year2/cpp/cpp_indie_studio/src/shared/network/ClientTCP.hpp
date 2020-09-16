//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// tcp encapsulation (client side)
//

#ifndef TCP_CLIENT_HPP_
#define TCP_CLIENT_HPP_

#include "Communicate.hpp"
#include "TCP.hpp"

/*
** the ClientTCP class enable connecting a client to a server
** it also encapsulate communication 
*/
class ClientTCP : public TCP {
public:
	/* creates a connection to the ip and port */
	ClientTCP(const std::string &ip, int port);

	/* creates a client from fd */
	ClientTCP(SOCKET fd);
	~ClientTCP();

	using TCP::getPort;
	using TCP::getIp;
	using TCP::getSocketFd;

	bool isOpen() const;

	template<typename T>
	void sendData(const T &);

	template<typename T>
	bool recvData(T &, bool = false);

private:
	void connectClient();

private:
	bool _connected;
};

template<typename T>
void ClientTCP::sendData(const T &obj)
{
	if (_connected)
		Communicate::sendData(_socket_fd, obj);
}

template<typename T>
bool ClientTCP::recvData(T &obj, bool blocking)
{
	if (!_connected)
		return (false);
	auto result = Communicate::recvData(_socket_fd, obj, blocking);

	if (result == StateFd::CLOSED)
		_connected = false;
	return (result == StateFd::READ);
}

#endif /* !TCP_CLIENT_HPP_ */
