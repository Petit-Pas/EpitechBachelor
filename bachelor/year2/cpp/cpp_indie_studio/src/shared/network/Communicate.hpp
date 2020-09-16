//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// encapsulation of data communication
//

#ifndef COMMUNICATE_HPP_
#define COMMUNICATE_HPP_

#if defined(WIN32)
#include <winsock2.h>
typedef int socklen_t;
#else

	#include <sys/socket.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>

	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#endif
#include <vector>
#include <iostream>

enum class StateFd {
	CLOSED,
	READ,
	NOTHING
};

class Communicate {
public:
	template<typename Type>
	static void sendData(SOCKET fd, const Type &);

	template<typename Type>
	static StateFd recvData(SOCKET fd, Type &, bool = false);

private:
	Communicate() = default;
	~Communicate() = default;
};

template<typename Type>
void Communicate::sendData(SOCKET fd, const Type &obj)
{
	send(fd, (const char *)&obj, sizeof(Type), 0);
	send(1, (const char *)&obj, sizeof(Type), 0);
}

template<typename Type>
StateFd Communicate::recvData(SOCKET fd, Type &obj, bool blocking)
{
	fd_set fdSet;
	timeval t = {0, blocking ? 200000 : 200};

	FD_ZERO(&fdSet);
	FD_SET(fd, &fdSet);
	int ret = select(FD_SETSIZE, &fdSet, nullptr, nullptr, &t);
	if (ret < 0)
		return (StateFd::NOTHING);
	if (FD_ISSET(fd, &fdSet)) {
		auto state = recv(fd, (char *)&obj, sizeof(Type), 0);
		if (state == 0)
			return (StateFd::CLOSED);
		else if (state > 0)
			return (StateFd::READ);
	} else if (blocking)
		return (StateFd::CLOSED);
	return (StateFd::NOTHING);
}

#endif /* !COMMUNICATE_HPP_ */
