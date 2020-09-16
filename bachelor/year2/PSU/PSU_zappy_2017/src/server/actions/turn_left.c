/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <memory.h>
#include "zappy_server_functions.h"

/**
 * function called for the Left command
 * @param player the player that rotates
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
const char *turn_left(player_t *player, data_t *data)
{
	if (player->direction == UP)
		player->direction = LEFT;
	else
		player->direction -= 1;
	dump_one_player(player, &data->graphical);
	return xstrdup("ok\n");
}
