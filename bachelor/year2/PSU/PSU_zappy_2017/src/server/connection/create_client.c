/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Client creation
*/

#include        <poll.h>
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <netinet/in.h>

/**
 * If a connection is trying to be established, this functions opens it
 * @param fd the socket of the server
 * @return the newly opened connection or -1 if no new
 * connection could be established
 */

int add_client(const int fd)
{
	struct sockaddr_in client_name;
	struct pollfd fds;
	socklen_t size;

	fds.fd = fd;
	fds.events = 0;
	fds.events = POLLIN;
	if (poll(&fds, 1, 0) > 0
		&& fds.revents != POLLERR
		&& fds.revents != POLLNVAL
		&& fds.revents != POLLHUP
		&& fds.revents == POLLIN) {
		size = sizeof(client_name);
		return (accept(fd, (struct sockaddr *)&client_name, &size));
	}
	return (-1);
}
