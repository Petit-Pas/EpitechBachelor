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
 * the function that dumps an inventory for the graphical clients
 * @param player the player concerned
 * @param graphical the graphical struct found in data_t
 */

void dump_inventory(const player_t *player, graphical_t *graphical)
{
	char result[256];

	sprintf(result, "pin %i %i %i %i %i %i %i %i %i %i\n", player->id,
		player->cell->pos.x, player->cell->pos.y,
		player->inventory.food, player->inventory.ressources[0],
		player->inventory.ressources[1],
		player->inventory.ressources[2],
		player->inventory.ressources[3],
		player->inventory.ressources[4],
		player->inventory.ressources[5]);
	send_to_graphical(result, graphical);
}
