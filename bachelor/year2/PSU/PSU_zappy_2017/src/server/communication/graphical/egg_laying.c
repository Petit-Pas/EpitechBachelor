/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stdio.h>
#include "zappy_server_functions.h"

/**
 * function that dumps an egg is laying to graphical clients
 * @param player player concerned
 * @param graphical graphical struct found in data_t
 */

void egg_laying(const player_t *player, graphical_t *graphical)
{
	char buf[512];

	sprintf(buf, "pfk %i\n", player->id);
	send_to_graphical(buf, graphical);
}
