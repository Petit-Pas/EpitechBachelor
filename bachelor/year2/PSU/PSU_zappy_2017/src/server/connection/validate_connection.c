/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "zappy_server_macros.h"
#include "zappy_server_functions.h"

/**
 * send the first information for a new player
 * @param fd fd of the player
 * @param data the struct containing all the datas about the server and the game
 * @param team the team fo the player
 * @return the return value of send_to_client()
 */

static int send_first_informations(const int fd, const data_t *data,
	const team_t *team)
{
	char mess[64];

	sprintf(mess, "%i\n%i %i\n",
		team->amount_of_max_connections - team->amount_of_players,
		data->size.x, data->size.y);
	return send_to_client(fd, mess);
}

/**
 * spawn a new player from an egg
 * @param team the team of the player
 * @param data the struct containing all the datas about the server and the game
 * @param fd the fd of the player
 */

static void create_player_from_egg(team_t *team, data_t *data, const int fd)
{
	player_t *new_player = spawn_player(team->name, data, POS_EGG(team).x,
		POS_EGG(team).y);
	player_t *stock = team->eggs->player;

	player_connection_egg(team->eggs->player, &data->graphical);
	team->eggs = remove_player_from_list(team->eggs, team->eggs->player);
	new_player->socket_fd = fd;
	new_player->should_close += send_first_informations(fd, data, team);
	circular_buf_reset(&new_player->buffer);
	free(stock);
	dump_new_player(data, new_player);
}

/**
 * spawn a player at a random location
 * @param team the team of the player
 * @param data the struct containing all the datas about the server and the game
 * @param fd the fd of the player
 */

static void create_player_from_nowhere(team_t *team, data_t *data, const int fd)
{
	player_t *new_player = spawn_player(team->name, data,
		rand() % data->size.x, rand() % data->size.y);

	new_player->socket_fd = fd;
	circular_buf_reset(&new_player->buffer);
	send_first_informations(fd, data, team);
	dump_new_player(data, new_player);
}

/**
 * remove connection from pending, and add it to graphical,
 * a given team, or nothing
 * @param data the struct containing all the datas about the server and the game
 * @param team_name the received team name during handshake
 * @param index the index of the pending connection
 */

void try_to_spawn_player(data_t *data, char *team_name, int index)
{
	team_t *team = get_team(data->teams, team_name);

	if (strcmp(team_name, "GRAPHIC") == 0)
		add_graphical_connection(data, index);
	else if (!team ||
		team->amount_of_max_connections == team->amount_of_players)
		close(data->pending[index]);
	else if (team->eggs)
		create_player_from_egg(team, data, data->pending[index]);
	else
		create_player_from_nowhere(team, data, data->pending[index]);
	while (index != MAX_PENDING_SIZE - 1 && data->pending[index] != 0) {
		data->pending[index] = data->pending[index + 1];
		index += 1;
	}
	data->pending[index] = 0;
}
