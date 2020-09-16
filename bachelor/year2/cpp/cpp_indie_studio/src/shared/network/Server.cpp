//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// tcp encapsulation (server side)
//

#include <stdexcept>
#include "Server.hpp"

ServerTCP::ServerTCP(const std::string &ip, int nb_max_client, int port) : TCP(ip, port)
{
	bindServerAndListen(nb_max_client);
}

ServerTCP::~ServerTCP()
{
	for (const auto &fd : _clients)
		closesocket(fd);
}

void ServerTCP::bindServerAndListen(int nb_clients)
{
	if (bind(_socket_fd, (SOCKADDR *)(&_s_in), sizeof(_s_in)) == -1) {
		throw (std::runtime_error("Binding failed with ip/port."));
	}
	if (listen(_socket_fd, nb_clients) == -1)
		throw (std::runtime_error("A socket is already listening on the port."));
	if (_port == 0)
		setRealPort();
}

void ServerTCP::setRealPort()
{
	SOCKADDR_IN sin;
	socklen_t len = sizeof(sin);

	if (getsockname(_socket_fd, (SOCKADDR *)&sin, &len) == -1)
		throw (std::runtime_error("cannot get port linked\n"));
	_port = ntohs(sin.sin_port);
}

int ServerTCP::acceptClient(bool blocking, int ms_time)
{
	fd_set fdSet;
	timeval t = {0, ms_time * 1000};

	FD_ZERO(&fdSet);
	FD_SET(_socket_fd, &fdSet);
	int ret = (blocking) ? 42 :
		select(FD_SETSIZE, &fdSet, nullptr, nullptr, &t);

	if (ret < 0)
		throw (std::runtime_error("Select error"));
	SOCKADDR_IN s_in_client;
	socklen_t len = sizeof(s_in_client);
	SOCKET client_fd = -1;
	if (blocking || FD_ISSET(_socket_fd, &fdSet)) {
		client_fd = accept(_socket_fd, (SOCKADDR *)(&s_in_client), &len);
		if (client_fd == INVALID_SOCKET)
			throw (std::runtime_error("Client cannot be accepted"));
	}
	if (client_fd != INVALID_SOCKET)
		_clients.push_back(client_fd);
	return (client_fd);
}

const std::vector<SOCKET> &ServerTCP::getClients() const
{
	return (_clients);
}

int ServerTCP::popClient(size_t nb)
{
	int fd = -1;

	if (nb < _clients.size()) {
		fd = _clients[nb];
		_clients.erase(_clients.begin() + nb);
	}
	return (fd);
}
