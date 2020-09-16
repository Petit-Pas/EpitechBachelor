//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// tcp encapsulation
//

#ifndef TCP_HPP_
#define TCP_HPP_


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
#include <stdexcept>
#include <string>

class TCP {
public:
	TCP(const std::string &ip = "any", int port = 0);
	TCP(SOCKET fd);
	~TCP();

	void setPort();
	int getPort() const;
	const std::string &getIp() const;
	SOCKET getSocketFd() const;

protected:
	SOCKET _socket_fd;
	const std::string _ip;
	int _port;
	SOCKADDR_IN _s_in;

private:
	void initSockaddr();
	void getTcpSocket();
	void setServerInfo();
};

#endif /* !TCP_HPP_ */
