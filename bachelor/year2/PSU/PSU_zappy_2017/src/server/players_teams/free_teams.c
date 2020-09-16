/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdlib.h>
#include "zappy_server_structs.h"
#include "zappy_server_functions.h"

/**
 * free a task queue
 * @param tasks the task queue to free
 */

void free_tasks(task_t *tasks)
{
	for (int i = 0; i != MAX_QUEUE_SIZE; i++)
		if (tasks[i].task != START_INCANTATION)
			free(tasks[i].additional_informations);
}

/**
 * free a player list + the players inside
 * @param players the player list
 */

void free_players(player_ll_t *players)
{
	player_ll_t *to_free;

	while (players != NULL) {
		to_free = players;
		players = players->next;
		free_tasks(to_free->player->tasks.tasks);
		free(to_free->player);
		free(to_free);
	}
}

/**
 * free a egg list + the eggs
 * @param eggs the list of eggs
 */

static void free_eggs(player_ll_t *eggs)
{
	player_ll_t *to_free;

	while (eggs != NULL) {
		to_free = eggs;
		eggs = eggs->next;
		free(to_free->player);
		free(to_free);
	}
}

/**
 * free the teams
 * @param teams array of teams
 */

void free_teams(team_t **teams)
{
	for (int i = 0; teams[i] != NULL; i++) {
		free_player_list(teams[i]->list_players);
		free_eggs(teams[i]->eggs);
		free(teams[i]->name);
		free(teams[i]);
	}
	free(teams);
}
