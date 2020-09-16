/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdlib.h>
#include "zappy_server_structs.h"

/**
 * frees a linked_list of players
 * @param list
 */

void free_player_list(player_ll_t *list)
{
	player_ll_t *tmp = list;
	player_ll_t *to_free;

	while (tmp != NULL) {
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
}

/**
 * free a cell from the map
 * @param cell cell to free
 */

static void free_cell(map_t *cell)
{
	free_player_list(cell->players_list);
	free(cell);
}

/**
 * frees the whole toric map
 * @param origin any node of the map
 * @param size size of the map
 */

void free_map_linked(map_t *origin, const vector_2i_t *size)
{
	map_t *next = origin->directions[DOWN];
	map_t *tmp = origin;
	map_t *to_free = NULL;

	origin->directions[UP]->directions[DOWN] = NULL;
	while (tmp != NULL) {
		tmp->directions[LEFT]->directions[RIGHT] = NULL;
		while (tmp != NULL) {
			to_free = tmp;
			tmp = tmp->directions[RIGHT];
			free_cell(to_free);
		}
		if (size->y == 1)
			return;
		tmp = next;
		if (next != NULL)
			next = next->directions[DOWN];
	}
}
