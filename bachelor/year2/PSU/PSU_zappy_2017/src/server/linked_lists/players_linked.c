/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdlib.h>
#include <memory.h>
#include "zappy_server_macros.h"
#include "zappy_server_functions.h"

/**
 * create a new player_ll_t * node
 * @param player the player_t to encapsulate
 * @return the newly allocated link
 */

player_ll_t *create_node_player_list(player_t *player)
{
	player_ll_t *new = xmalloc(sizeof(player_ll_t));

	memset(new, 0, sizeof(player_ll_t));
	new->player = player;
	return new;
}

/**
 * append a given node to a player list
 * @param list the list to complete
 * @param to_add the node to add
 * @return the new list
 * \warning should be used so : list = append_to_player_list(list, node)
 */

player_ll_t *append_to_player_list(player_ll_t *list, player_ll_t *to_add)
{
	if (to_add == NULL)
		return list;
	if (list == NULL)
		return to_add;
	to_add->next = list;
	return to_add;
}

/**
 * remove a given link from a player list
 * @param list the list to be removed from
 * @param to_remove the link to remove
 * @return the new list
 * \warning should be used like append_to_player_list()
 */

player_ll_t *remove_link_from_player_list(player_ll_t *list,
	player_ll_t *to_remove)
{
	player_ll_t *tmp = list;
	player_ll_t *prev_tmp = list;

	if (list == to_remove) {
		tmp = list->next;
		free(list);
		return tmp;
	}
	while (tmp != to_remove) {
		prev_tmp = tmp;
		tmp = tmp->next;
	}
	prev_tmp->next = tmp->next;
	free(tmp);
	return list;
}

/**
 * remove a given player from a player list
 * @param list the given list
 * @param to_remove the player to remove
 * @return the new list
 * \warning should be used like append_to_player_list()
 */

player_ll_t *remove_player_from_list(player_ll_t *list, player_t *to_remove)
{
	player_ll_t *tmp = list;
	player_ll_t *prev_tmp = list;

	if (list->player == to_remove) {
		tmp = list->next;
		free(list);
		return tmp;
	}
	while (tmp->player != to_remove) {
		prev_tmp = tmp;
		tmp = tmp->next;
	}
	prev_tmp->next = tmp->next;
	free(tmp);
	return list;
}
