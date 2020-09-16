/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "zappy_server_functions.h"

/**
 * main function called when using Inventory command
 * @param player the player that calls this command
 * @param data the struct containing every information about the server
 * @return the answer form the server
 */
const char *inventory(player_t *player, __attribute__((unused)) data_t *data)
{
	char *answer = xmalloc(sizeof(char) * 256);

	snprintf(answer, 256, "[food %i, linemate %i, deraumere %i, sibur %i, "
			      "mendiane %i, phiras %i, thystame %i]\n",
		player->inventory.food, player->inventory.ressources[0],
		player->inventory.ressources[1],
		player->inventory.ressources[2],
		player->inventory.ressources[3],
		player->inventory.ressources[4],
		player->inventory.ressources[5]);
	return answer;
}
