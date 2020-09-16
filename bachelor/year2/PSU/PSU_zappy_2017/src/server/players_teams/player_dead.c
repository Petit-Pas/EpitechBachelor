/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "zappy_server_functions.h"
#include "zappy_server_macros.h"

/**
 * remove player from hiw own cell
 * @param player the given player
 */

static void remove_player_from_cell(player_t *player)
{
	PLAYER_LIST_CELL(player) =
		remove_player_from_list(PLAYER_LIST_CELL(player), player);
}

/**
 * remove player from his own team
 * @param player
 */

static void remove_player_from_team(player_t *player)
{
	if (player->level == LEVEL_MAX)
		player->team->amount_of_max_level_players -= 1;
	player->team->list_players =
		remove_player_from_list(player->team->list_players, player);
	player->team->amount_of_players -= 1;
}

/**
 * set food on the ground while a player dies
 * @param dead player who died
 * @param data struct containing all informations for the server and the game
 */

static void set_resources_dead(player_t *dead, data_t *data)
{
	for (int i = 0; i != AMOUNT_RESSOURCES; i++)
		dead->cell->resources[i] += dead->inventory.ressources[i];
	dead->cell->food += dead->inventory.food;
	bct(data, dead->cell);
}

/**
 * erase a player that dies (or disconnects)
 * @param player the given player
 * @param data the struct containing every information about the server
 */

void player_dead(player_ll_t *player, data_t *data)
{
	player_t *tmp = player->player;

	set_resources_dead(player->player, data);
	player_death(player->player, &data->graphical);
	send_to_client(player->player->socket_fd, "dead\n");
	close(player->player->socket_fd);
	free_tasks(player->player->tasks.tasks);
	remove_player_from_cell(player->player);
	remove_player_from_team(player->player);
	data->players = remove_player_from_list(data->players, player->player);
	bct(data, tmp->cell);
	free(tmp);
}
