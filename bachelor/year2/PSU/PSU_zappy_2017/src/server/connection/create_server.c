/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** server creation functions
*/

#include        <ctype.h>
#include        <stdio.h>
#include        <unistd.h>
#include        <stdlib.h>
#include        <netdb.h>
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <netinet/in.h>

/**
 * verify if the port given is a valid port
 * @param port the port to check
 * @return 0 if the port is invalid, 1 otherwise
 */

static int check_port(const int port)
{
	if (port > 65535 || port < 1) {
		dprintf(2, "The port must be a number between 1 "
			   "and 65535.\n");
		return (0);
	}
	return (1);
}

/**
 * binds the given port to the given fd, and listen
 * @param port the given port
 * @param fd the given fd
 * @return -1 if an error occurred, 0 otherwise
 */

static int bind_port(const uint16_t port, const int fd)
{
	struct sockaddr_in s_in;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		close(fd);
		return (-1);
	}
	if (listen(fd, 1000) == -1) {
		close(fd);
		return (-1);
	}
	return (0);
}

/**
 * launch the server on the given port
 * @param port given port
 * @return -1 if an error occurred, 0 otherwise
 */

static int launch_server(const uint16_t port)
{
	struct protoent *pe = getprotobyname("TCP");
	int fd;

	if (pe == NULL)
		return (-1);
	fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, pe->p_proto);
	if (fd == -1)
		return (-1);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
	if (bind_port(port, fd) == -1)
		return (-1);
	return (fd);
}

/**
 * creates the server
 * @param port the given port
 * @return the fd corresponding to the opened socket, -1 if an error occurred
 */

int server_creation(int port)
{
	if (check_port(port) != 1)
		return (-1);
	return (launch_server((uint16_t)port));
}
