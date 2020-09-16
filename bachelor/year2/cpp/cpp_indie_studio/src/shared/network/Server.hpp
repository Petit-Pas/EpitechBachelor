//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// tcp encapsulation (server side)
//

#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_

#include <vector>
#include "TCP.hpp"

class ServerTCP : public TCP {
public:
	ServerTCP(const std::string &ip = "any", int nb_client = 256, int port = 0);
	~ServerTCP();

	using TCP::getPort;
	using TCP::getIp;
	using TCP::getSocketFd;

	int acceptClient(bool blocking = true, int ms_time = 5);
	const std::vector<SOCKET> &getClients() const;
	int popClient(size_t = 0);

private:
	void bindServerAndListen(int);
	void setRealPort();

private:
	std::vector<SOCKET> _clients;
};

#endif /* !TCP_SERVER_HPP_ */
