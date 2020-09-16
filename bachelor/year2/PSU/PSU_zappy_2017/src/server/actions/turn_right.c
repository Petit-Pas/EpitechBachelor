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
 * function called for the Right command
 * @param player the player that rotates
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
 const char *turn_right(player_t *player, __attribute__((unused))data_t *data)
{
	if (player->direction == LEFT)
		player->direction = UP;
	else
		player->direction += 1;
	dump_one_player(player, &data->graphical);
	return xstrdup("ok\n");
}
