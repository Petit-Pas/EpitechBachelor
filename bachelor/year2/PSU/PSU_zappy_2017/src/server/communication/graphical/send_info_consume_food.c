/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include "zappy_server_functions.h"

/**
 * send the information that a player eats to graphical clients
 * @param player the player that eats
 * @param graphical the graphical struct found in data_t
 */

void send_info_consume_food(player_t *player, graphical_t *graphical)
{
	char buf[128];

	sprintf(buf, "fed %i\n", player->id);
	send_to_graphical(buf, graphical);
}
