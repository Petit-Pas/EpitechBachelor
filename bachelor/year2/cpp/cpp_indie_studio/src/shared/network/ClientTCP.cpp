//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// tcp encapsulation (client side)
//

#include <stdexcept>
#include <iostream>
#include "ClientTCP.hpp"

ClientTCP::ClientTCP(const std::string &ip, int port) : TCP(ip, port), _connected(true)
{
	connectClient();
}

ClientTCP::ClientTCP(SOCKET fd) : TCP(fd), _connected(true)
{
}

ClientTCP::~ClientTCP()
{
}

void ClientTCP::connectClient()
{
	if (connect(_socket_fd, (SOCKADDR *)(&_s_in), sizeof(_s_in)) == -1)
		throw (std::runtime_error("Unable to connect to server"));
}

bool ClientTCP::isOpen() const
{
	return (_connected);
}
