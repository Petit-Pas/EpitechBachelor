/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Created by vincent,
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "zappy_server_functions.h"

static bool valid_request(player_t *player, char *buffer,
	const unsigned short write_bytes)
{
	char tmp_character = 0;

	for (unsigned short i = 0; i < write_bytes; ++i) {
		tmp_character = circular_buf_get(&player->buffer);
		buffer[i] = tmp_character;
	}
	buffer[write_bytes - 1] = 0;
	return (true);
}

static bool get_request(player_t *player, char *buffer)
{
	char character = 0;
	unsigned short write_bytes = 0;
	ssize_t read_bytes = read(player->socket_fd, &character, 1);

	while (read_bytes > 0 && !circular_buf_is_full(&player->buffer)) {
		circular_buf_put(&player->buffer, character);
		write_bytes++;
		if (character == '\n')
			return (valid_request(player, buffer, write_bytes));
		read_bytes = read(player->socket_fd, &character, 1);
	}
	if (read_bytes > 0) {
		player->buffer.write_idx = player->buffer.read_idx;
		return (true);
	}
	return (false);
}

bool handle_client_request(player_t *player, char *buffer)
{
	struct pollfd fds = {player->socket_fd, POLLIN, 0};

	if (poll(&fds, 1, 0) > 0
		&& fds.revents != POLLERR
		&& fds.revents != POLLNVAL
		&& fds.revents != POLLHUP
		&& fds.revents == POLLIN)
		return (get_request(player, buffer));
	return (true);
}