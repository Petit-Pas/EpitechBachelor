/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include "zappy_server_structs.h"

/**
 * dump the map
 * @param origin 0;0
 */

void dump_map_debug(map_t *origin)
{
	map_t *tmp = origin;
	map_t *stock_start_line = tmp;

	do {
		do {
			printf("%02i:%02i, ", tmp->pos.x, tmp->pos.y);
			tmp = tmp->directions[RIGHT];
		} while (stock_start_line != tmp);
		printf("\n");
		stock_start_line = stock_start_line->directions[DOWN];
		tmp = stock_start_line;
	} while (stock_start_line != origin);
}

/**
 * dump every player
 * @param list player list
 */

void dump_players(player_ll_t *list)
{
	player_ll_t *tmp = list;

	while (tmp != NULL) {
		printf("player in %i, %i \tlooking at %i\n",
			tmp->player->cell->pos.x, tmp->player->cell->pos.y,
			tmp->player->direction);
		tmp = tmp->next;
	}
}
