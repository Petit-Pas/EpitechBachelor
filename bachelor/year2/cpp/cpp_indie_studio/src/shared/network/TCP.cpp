//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// tcp encapsulation
//

#include "TCP.hpp"

TCP::TCP(const std::string &ip, int port) : _ip(ip), _port(port)
{
	#if defined(WIN32)
	WSADATA WSAData;
        WSAStartup(MAKEWORD(2, 2), &WSAData);
	#endif
	setServerInfo();
}

TCP::TCP(SOCKET fd) : _socket_fd(fd)
{
	setPort();
}

TCP::~TCP()
{
	closesocket(_socket_fd);
	#if defined(WIN32)
	WSACleanup();
	#endif
}

void TCP::setPort()
{
	SOCKADDR_IN sin;
	socklen_t len = sizeof(sin);

	if (getsockname(_socket_fd, (SOCKADDR *)&sin, &len) == SOCKET_ERROR)
		throw (std::runtime_error("cannot get port linked\n"));
	_port = ntohs(sin.sin_port);
}

void TCP::getTcpSocket()
{
	_socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket_fd == INVALID_SOCKET)
		throw (std::runtime_error("Cannot create socket for TCP"));
}

void TCP::initSockaddr()
{
	_s_in.sin_family = AF_INET;
	_s_in.sin_port = (_port != 0) ? (htons(_port)) : (0);
	if (_ip == "any")
		_s_in.sin_addr.s_addr = INADDR_ANY;
	#if defined(WIN32)
	_s_in.sin_addr.s_addr = inet_addr(_ip.c_str());
	#else
	else if (inet_pton(AF_INET, _ip.c_str(), &_s_in.sin_addr) != 1) {
		throw (std::runtime_error("Conversion ip to binary failed."));
	}
	#endif
}

void TCP::setServerInfo()
{
	getTcpSocket();
	int opt = 1;
	setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR,
		(const char*)&opt, sizeof(int));
	initSockaddr();
}

int TCP::getPort() const
{
	return (_port);
}

const std::string &TCP::getIp() const
{
	return (_ip);
}

SOCKET TCP::getSocketFd() const
{
	return (_socket_fd);
}
