/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <stdio.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * dump the level of 1 player to graphical clients
 * @param player the player concerned
 * @param graphical the graphical struct found in data_t
 */

void dump_level(const player_t *player, graphical_t *graphical)
{
	char result[128];

	sprintf(result, "plv %i %i\n", player->id, player->level);
	send_to_graphical(result, graphical);
}
