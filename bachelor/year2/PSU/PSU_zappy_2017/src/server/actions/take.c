/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <memory.h>
#include "zappy_server_structs.h"
#include "zappy_server_functions.h"

/**
 * A function to take food from the map to a player
 * @param player the player that takes
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
static char *take_food(player_t *player, data_t *data)
{
	if (player->cell->food == 0)
		return xstrdup("ko\n");
	player->cell->food -= 1;
	player->inventory.food += 1;
	resource_collecting(player, &data->graphical, 0);
	return xstrdup("ok\n");
}

/**
 * a function to take resource from the map, and give it to a player
 * @param player the player that takes
 * @param index the index of the taken resources
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
static const char *take_resources(player_t *player, const int index,
	data_t *data)
{
	if (player->cell->resources[index] == 0) {
		printf("could not pick up %i\n", index);
		return xstrdup("ko\n");
	}
	player->cell->resources[index] -= 1;
	player->inventory.ressources[index] += 1;
	resource_collecting(player, &data->graphical, index + 1);
	return xstrdup("ok\n");
}

/**
 * main function for Take command
 * @param player the player that takes
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
const char *take(player_t *player, data_t *data)
{
	const task_t *task = get_head_queue(&player->tasks);
	const int index = get_index_global(resources_g,
		task->additional_informations);

	if (index == -1) {
		if (strcmp("food", task->additional_informations) == 0)
			return take_food(player, data);
		else
			return xstrdup("ko\n");
	}
	return take_resources(player, index, data);
}
