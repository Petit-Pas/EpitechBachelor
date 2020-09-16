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
 * main function called for the Fork command
 * @param player the player that forks
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
const char *fork_player(player_t *player, __attribute__((unused)) data_t *data)
{
	player_t *new = xmalloc(sizeof(player_t));

	memset(new, 0, sizeof(player_t));
	new->level = 1;
	new->team = player->team;
	new->direction = rand() % 4;
	new->waited_for = 0;
	new->time_tic_left = 0;
	new->inventory.food = 10;
	new->cell = player->cell;
	new->team->eggs = append_to_player_list(new->team->eggs,
		create_node_player_list(new));
	new->id = get_unique_id();
	egg_laid(player, new, &data->graphical);
	return xstrdup("ok\n");
}
