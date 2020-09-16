/*
** EPITECH PROJECT, 2018
** Graphical
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#ifndef GRAPHICAL_CONNECTION_HPP
#define GRAPHICAL_CONNECTION_HPP

#include <string>
#include <queue>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdexcept>

#define MAX_LENGTH 4096

class Connection {
public:
	/**
	 * Constructor uses the ip address and port of the server to create the
	 * connection.
	 * @param addr Server's address
	 * @param port Server's port
	 */
	Connection(const std::string &addr, int port);
	~Connection();

	/**
	 * Non-blocking read on the server
	 * @return false if something went wrong
	 */
	bool receiveMsg();

	/**
	 * Sends a message on the server
	 * @param msg Message to send
	 */
	void sendMsg(const std::string &msg);

	/**
	 * Gets the next message of the queue
	 * @return The first element of the message queue
	 */
	std::string getNextMessage();

	bool hasMessages() const
	{
		return !_messages.empty();
	}

	bool isConnected() const
	{
		return _connected;
	}

private:
	bool _connected;
	std::string _addr;
	unsigned short _port;
	int _socket;
	sockaddr_in _s_in;
	fd_set _fdSet;
	std::queue<std::string> _messages;
	std::string _uncomplete;
	bool _complete;
};

#endif //GRAPHICAL_CONNECTION_HPP
