/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stdio.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * dump the death of a player to graphical clients
 * @param player the player concerned
 * @param graphical the graphical struct found in data_t
 */

void player_death(const player_t *player, graphical_t *graphical)
{
	char buf[512];
	sprintf(buf, "pdi %i\n", player->id);
	send_to_graphical(buf, graphical);
}
