/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "zappy_server_macros.h"
#include "zappy_server_functions.h"

/**
 * removes a tic of lfe to the player and feed him if needed
 * @param player the player to feed
 * @param graphical the sutrcut containing graphical clients, found in data_t
 * @return -1 if the player died, 0 otherwise
 */

static int feed(player_t *player, data_t *data)
{
	if (player->time_tic_left == 0) {
		if (player->inventory.food == 0)
			return -1;
		player->inventory.food -= 1;
		player->time_tic_left += FOOD_VALUE;
		send_info_consume_food(player, &data->graphical);
		food_spawn(data);
	}
	player->time_tic_left -= 1;
	if (player->tasks.size != 0)
		player->waited_for += 1;
	return 0;
}

/**
 * check if an action has to be done for a player
 * @param player the player to check
 * @param data a struct containing informations about server and game
 */

static void check_action_done(player_t *player, data_t *data)
{
	if (player->tasks.size == 0)
		return;
	task_t *task = get_head_queue(&player->tasks);
	int incanted = 0;

	while (player->tasks.size &&
		(time_consumption_g[task->task] <= player->waited_for ||
			(START_OF_INCANTATION(player))) && incanted == 0) {
		if (START_OF_INCANTATION(player))
			incanted = 1;
		const char *ans = actions_array_g[task->task](player, data);
		player->should_close += send_to_client(player->socket_fd, ans);
		player->waited_for = 0;
		if (incanted == 0 || (ans[0] == 'k' && ans[1] == 'o'))
			pop_task(&player->tasks);
		free((char *)ans);
		task = get_head_queue(&player->tasks);
	}
}

/**
 * rot an egg -> aka kill it
 * @param team the team of the egg
 * @param tmp the egg
 * @param data a struct containing informations about server and game
 * @return the pointer of the next egg
 */

static player_ll_t *rot_eggs(team_t *team, player_ll_t *tmp, data_t *data)
{
	player_ll_t *st;
	player_t *player;

	team->amount_of_max_connections -= 1;
	st = tmp;
	tmp = tmp->next;
	player = st->player;
	team->eggs = remove_player_from_list(team->eggs, player);
	dump_rotten_egg(data, player);
	free(player);
	return tmp;
}

/**
 * hatch every egg of a team a bit, rot the too olds
 * @param team the given team
 * @param data a struct containing informations about server and game
 */

static void hatch_eggs(team_t *team, data_t *data)
{
	player_ll_t *tmp = team->eggs;

	while (tmp != NULL) {
		tmp->player->waited_for += 1;
		if (tmp->player->waited_for == HATCHING_TIME) {
			egg_hatch(tmp->player, &data->graphical);
			team->amount_of_max_connections += 1;
		}
		if (tmp->player->waited_for == 3 * HATCHING_TIME) {
			tmp = rot_eggs(team, tmp, data);
		} else
			tmp = tmp->next;
	}
}

/**
 * update every players in term of action and eggs in term of hatch/rot
 * @param data a struct containing informations about server and game
 */

void update_players(data_t *data)
{
	player_ll_t *tmp = data->players;
	player_ll_t *stock = NULL;
	int i = 0;

	while (tmp != NULL) {
		if (tmp->player->should_close == 0)
			check_action_done(tmp->player, data);
		if (feed(tmp->player, data) == -1 ||
			tmp->player->should_close != 0) {
			stock = tmp;
			tmp = tmp->next;
			player_dead(stock, data);
		} else {
			check_action_done(tmp->player, data);
			tmp = tmp->next;
		}
	}
	while (data->teams[i] != NULL) {
		hatch_eggs(data->teams[i], data);
		i += 1;
	}
}
