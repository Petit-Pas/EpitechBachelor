/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "zappy_server_functions.h"

/**
 * send start incantation to graphical clients
 * @param player the player that incants
 * @param graphical the graphical struct that can be found in data_t
 */

void dump_start_incantation(const player_t *player, graphical_t *graphical)
{
	char *mess = xmalloc(64);
	player_ll_t *tmp = player->cell->players_list;

	sprintf(mess, "pic %i %i %i", player->cell->pos.x, player->cell->pos.y,
		player->level);
	while (tmp != NULL) {
		append_int_to_string(&mess, tmp->player->id);
		tmp = tmp->next;
	}
	send_to_graphical(mess, graphical);
	free(mess);
}
