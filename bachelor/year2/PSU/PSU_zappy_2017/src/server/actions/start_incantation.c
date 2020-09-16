/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "zappy_server_macros.h"
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * function that checks if every needed condition to incant are OK
 * @param player
 * @return
 */
static int meets_condition(player_t *player)
{
	const int amount_players = count_players_by_level(
		PLAYER_LIST_CELL(player), player->level);

	if (player->level == LEVEL_MAX)
		return 0;
	if (amount_players == -1)
		return 0;
	if (NEEDED_PLAYERS(player) != amount_players)
		return 0;
	for (int i = 0; i != AMOUNT_RESSOURCES; i += 1) {
		if (NEEDED_RESOURCES(player)[i] != player->cell->resources[i])
			return 0;
	}
	return 1;
}

/**
 * refresh the count of mal level players for a team
 * @param player the player that leveld up
 * @param data the struct containing every information about the server
 */
static void refresh_max_level_count(player_t *player, data_t *data)
{
	player->team->amount_of_max_level_players += 1;
	if (player->team->amount_of_max_level_players ==
		AMOUNT_OF_MAX_LEVEL_NEEDED) {
		player->team->has_won = 1;
		data->is_over = 1;
		end_g = 1;
		printf("Congratulation ! The player %d",player->id);
		printf(" of team %s won !!!\n",player->team->name);
	}
}

/**
 * level up players and tell them
 * @param player the player that incanted
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
static const char *trigger_elevation(player_t *player, data_t *data)
{
	player_ll_t *tmp = player->cell->players_list;
	char *message = xmalloc(sizeof(char) * 128);

	sprintf(message, "Current level: %i\n", player->level + 1);
	while (tmp != NULL) {
		tmp->player->level += 1;
		dump_level(tmp->player, &data->graphical);
		if (tmp->player != player)
			tmp->player->should_close += send_to_client(
				tmp->player->socket_fd, message);
		tmp = tmp->next;
	}
	bct(data, player->cell);
	if (player->level == LEVEL_MAX)
		refresh_max_level_count(player, data);
	return message;
}

/**
 * send a message to concerned players to let them now that
 * an incantation in on the way
 * @param player the player that incants
 * @return the answer of the server
 */
static const char *send_elevation_underway(player_t *player)
{
	player_ll_t *tmp = player->cell->players_list;
	char *message = xstrdup("Elevation underway\n");

	while (tmp != NULL) {
		if (tmp->player != player)
			tmp->player->should_close += send_to_client(
				tmp->player->socket_fd, message);
		tmp = tmp->next;
	}
	return message;
}

/**
 * The main function called for the Incantation command
 * @param player the player that incants
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
const char *start_incantation(player_t *player, data_t *data)
{
	if (player->tasks.tasks[0].additional_informations == NULL) {
		if (meets_condition(player) == 0)
			return xstrdup("ko\n");
		player->tasks.tasks[0].additional_informations =
			(char *)player->cell;
		dump_start_incantation(player, &data->graphical);
		return send_elevation_underway(player);
	} else {
		player->tasks.tasks[0].additional_informations = NULL;
		if (meets_condition(player) == 0) {
			dump_end_incantation(player->cell, &data->graphical, 0);
			return xstrdup("ko\n");
		}
		dump_end_incantation(player->cell, &data->graphical, 1);
		return (trigger_elevation(player, data));
	}
}
