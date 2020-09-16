/*
** EPITECH PROJECT, 2018
** Graphical
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#include <cstring>
#include "Utils.hpp"
#include "Connection.hpp"

Connection::Connection(const std::string &addr, int port) : _connected(false), _addr(addr), _port((unsigned short)port),
	_socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)), _complete(true)
{
	_s_in.sin_family = AF_INET;
	_s_in.sin_port = htons(_port);
	if (inet_pton(AF_INET, _addr.c_str(), &_s_in.sin_addr) == -1)
		throw std::runtime_error("Error trying to convert the IP address");
	else if (connect(_socket, (const sockaddr *)&_s_in, sizeof(_s_in)) == -1)
		throw std::runtime_error("Can't connect on the server");
	_connected = true;
}

Connection::~Connection()
{
	close(_socket);
}

bool Connection::receiveMsg()
{
	timeval t = {0, 100};
	char buffer[MAX_LENGTH];

	FD_ZERO(&_fdSet);
	FD_SET(_socket, &_fdSet);
	int ret = select(_socket + 1, &_fdSet, nullptr, nullptr, &t);

	if (ret == -1)
		return false;
	if (FD_ISSET(_socket, &_fdSet)) {
		memset(buffer, 0, MAX_LENGTH);
		ssize_t bytes(recv(_socket, buffer, MAX_LENGTH - 1, 0));
		if (bytes > 0) {
			std::vector<std::string> lines(Utils::split(buffer, '\n'));
			if (!_complete) {
				if (buffer[0] == '\n')
					_messages.push(_uncomplete);
				else
					lines[0] = _uncomplete + lines[0];
			}
			if (bytes == MAX_LENGTH - 1 && buffer[bytes - 1] != '\n') {
				_uncomplete = lines.back();
				_complete = false;
			} else
				_complete = true;
			size_t idx = 0;

			for (const auto &tmp : lines) {
				if (!(bytes == MAX_LENGTH - 1 && buffer[bytes - 1] != '\n' && idx == lines.size() - 1))
					_messages.push(tmp);
				idx++;
			}
		} else if (bytes == 0)
			throw std::runtime_error("Connection closed");
	}
	return true;
}

void Connection::sendMsg(const std::string &msg)
{
	dprintf(_socket, "%s%s", msg.c_str(), "\n");
}

std::string Connection::getNextMessage()
{
	std::string nextMessage(_messages.front());

	_messages.pop();
	return nextMessage;
}