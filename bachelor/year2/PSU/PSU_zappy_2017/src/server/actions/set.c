/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <memory.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * function to set food from a player to the map
 * @param player the player that sets food
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
static char *set_food(player_t *player, data_t *data)
{
	if (player->inventory.food <= 0)
		return xstrdup("ko\n");
	player->inventory.food -= 1;
	player->cell->food += 1;
	resource_dropping(player, &data->graphical, 0);
	return xstrdup("ok\n");
}

/**
 * a function to set resources from a player to the map
 * @param player the player that sets resources
 * @param index the index of the wanted resources
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
static const char *set_resources(player_t *player, const int index,
				data_t *data)
{
	if (player->inventory.ressources[index] == 0)
		return xstrdup("ko\n");
	player->cell->resources[index] += 1;
	player->inventory.ressources[index] -= 1;
	resource_dropping(player, &data->graphical, index + 1);
	return xstrdup("ok\n");
}

/**
 * the main function called for the Set command
 * @param player the player that sets
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
const char *set(player_t *player, data_t *data)
{
	const task_t *task = get_head_queue(&player->tasks);
	const int index = get_index_global(resources_g,
		task->additional_informations);

	if (index == -1) {
		if (strcmp("food", task->additional_informations) == 0)
			return set_food(player, data);
		else
			return xstrdup("ko\n");
	}
	return set_resources(player, index, data);
}
