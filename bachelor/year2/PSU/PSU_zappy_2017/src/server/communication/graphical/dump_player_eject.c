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
 * the function that dumps the Eject command to graphical clients
 * @param player the player ejected
 * @param graphical the graphical struct that can be found in data_t
 */

void dump_player_eject(const player_t *player, graphical_t *graphical)
{
	char result[128];

	sprintf(result, "pex %i\n", player->id);
	send_to_graphical(result, graphical);
}
