/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** read from client and write to client
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

static bool get_team_name(const int fd, char *buffer)
{
	for (unsigned short i = 0; i < 512; ++i) {
		char character;
		const ssize_t read_bytes = read(fd, &character, 1);
		if (read_bytes < 1)
			break;
		else if (character == '\n') {
			buffer[i] = 0;
			return (true);
		} else
			buffer[i] = character;
	}
	memset(buffer, 0, 512);
	return (false);
}

bool handle_new_client_request(const int fd, char *buffer)
{
	struct pollfd fds = {fd, POLLIN, 0};

	if (poll(&fds, 1, 0) > 0
		&& fds.revents != POLLERR
		&& fds.revents != POLLNVAL
		&& fds.revents != POLLHUP
		&& fds.revents == POLLIN)
		return (get_team_name(fd, buffer));
	return (true);
}

int sigpipe_g = 0;

/**
 * sighandler for SIGPIPE
 * @param signum unused
 */

void handle_sigpipe(__attribute__((unused)) int signum)
{
	sigpipe_g = 1;
}

/**
 * send a message to client and catch SIGPIPE
 * @param fd the fd on which the message is send;
 * @param msg the message to send
 * @return 1 if the client exited, 0 in other case
 */

int send_to_client(const int fd, const char *msg)
{
	signal(SIGPIPE, handle_sigpipe);
	dprintf(fd, "%s", msg);
	if (sigpipe_g == 1) {
		sigpipe_g = 0;
		return 1;
	}
	return 0;
}
