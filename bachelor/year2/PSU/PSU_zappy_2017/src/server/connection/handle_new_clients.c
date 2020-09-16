/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * add a newly opened connection to the pending connection
 * (waiting for team name)
 * @param data the struct containing all the datas about the server and the game
 * @param fd the newly opened connection
 */

static void add_to_pending(data_t *data, const int fd)
{
	int i = 0;

	while (i != MAX_PENDING_SIZE) {
		if (data->pending[i] == 0 &&
			send_to_client(fd, "WELCOME\n") == 1) {
			break;
		} else if (data->pending[i] == 0) {
			data->pending[i] = fd;
			return;
		}
		i += 1;
	}
	close(fd);
}

/**
 * open a new connection and add it to pending connection list
 * @param data the struct containing all the datas about the server and the game
 */

void check_new_client(data_t *data)
{
	const int new_fd = add_client(data->server_fd);

	if (new_fd == -1)
		return;
	printf("opened %i\n", new_fd);
	add_to_pending(data, new_fd);
}

/**
 * close a pending connection because of disconnection or wrong team name
 * @param data the struct containing all the datas about the server and the game
 * @param i the index of the pending connection
 */

void close_pending(data_t *data, int i)
{
	while (i != MAX_PENDING_SIZE - 1 && data->pending[i]) {
		data->pending[i] = data->pending[i + 1];
		i += 1;
	}
}

/**
 * check every pending connection to see if an answer has been received
 * @param data the struct containing all the datas about the server and the game
 */

void check_pendings(data_t *data)
{
	int i = 0;
	char team_name[512];

	memset(team_name, 0, 512);
	while (data->pending[i] && i != MAX_PENDING_SIZE) {
		if (!handle_new_client_request(data->pending[i], team_name)) {
			close_pending(data, i);
			i--;
		} else if (team_name[0]) {
			try_to_spawn_player(data, team_name, i);
			memset(team_name, 0, 512);
		}
		i++;
	}
}
