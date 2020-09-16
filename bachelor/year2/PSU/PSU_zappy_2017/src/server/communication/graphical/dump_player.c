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
 * dump 1 player's informations to graphical clients
 * @param player the player concerned
 * @param graphical the graphical struct found in data_t
 */

void dump_one_player(const player_t *player, graphical_t *graphical)
{
	char result[128];

	sprintf(result, "ppo %i %i %i %i\n", player->id, player->cell->pos.x,
		player->cell->pos.y, player->direction);
	send_to_graphical(result, graphical);
}

/**
 * dump all players a cell to graphical clients
 * @param cell the cell concerned
 * @param graphical the graphical struct that can be found in data_t
 */

void dump_players_cell(const map_t *cell, graphical_t *graphical)
{
	player_ll_t *tmp = cell->players_list;

	while (tmp != NULL) {
		dump_one_player(tmp->player, graphical);
		tmp = tmp->next;
	}
}
