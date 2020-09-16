/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stdio.h>
#include "zappy_server_structs.h"
#include "zappy_server_functions.h"

/**
 * dumps a new player to graphica clients
 * @param data the struct containing every information about the server
 * @param player the player concerned
 */

void dump_new_player(data_t *data, const player_t *player)
{
	char buf[512];

	sprintf(buf, "pnw %i %i %i %i %i %s\n", player->id, player->cell->pos.x,
		player->cell->pos.y, player->direction, player->level,
		player->team->name);
	send_to_graphical(buf, &data->graphical);
}

/**
 * dump a player to a given fd
 * @param player the player concerned
 * @param fd the given fd
 */

void pnw_one_client(const player_t *player, const int fd)
{
	char buf[512];

	sprintf(buf, "pnw %i %i %i %i %i %s\n", player->id, player->cell->pos.x,
		player->cell->pos.y, player->direction, player->level,
		player->team->name);
	send_to_client(fd, buf);
}
