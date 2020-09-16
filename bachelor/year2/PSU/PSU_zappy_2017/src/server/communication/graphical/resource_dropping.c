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
 * dumps the drop of a resource to grahical clients
 * @param player the player concerned
 * @param graphical the graphical struct found in data_t
 * @param resource_number the index of the dropped resource
 */

void resource_dropping(const player_t *player, graphical_t *graphical,
	const int resource_number)
{
	char buf[512];

	sprintf(buf, "pdr %i %i\n", player->id, resource_number);
	send_to_graphical(buf, graphical);
}
