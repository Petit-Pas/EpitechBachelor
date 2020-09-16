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
 * fumps the collect of a resource
 * @param player the player concerned
 * @param graphical the graphical sutrcut found in data_t
 * @param resource_number the index of the resource
 */

void resource_collecting(const player_t *player, graphical_t *graphical,
	const int resource_number)
{
	char buf[512];

	sprintf(buf, "pgt %i %i\n", player->id, resource_number);
	send_to_graphical(buf, graphical);
}
