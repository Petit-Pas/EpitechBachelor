/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdlib.h>
#include "zappy_server_structs.h"

/**
 * count the players in a player list
 * @param list the player list
 * @return the amount of player found
 */

int count_players(player_ll_t *list)
{
	player_ll_t *tmp = list;
	int i = 0;

	while (tmp != NULL) {
		tmp = tmp->next;
		i += 1;
	}
	return i;
}

/**
 * count the amount of players of the given level
 * @param list list of players
 * @param level level wanted
 * @return the amount of players, -1 if a player of another level was found
 */

int count_players_by_level(player_ll_t *list, const int level)
{
	player_ll_t *tmp = list;
	int i = 0;

	while (tmp != NULL) {
		i += 1;
		if (tmp->player->level != level)
			return -1;
		tmp = tmp->next;
	}
	return i;
}
