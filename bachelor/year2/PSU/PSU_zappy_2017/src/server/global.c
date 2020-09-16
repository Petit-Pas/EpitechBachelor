/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stddef.h>
#include <memory.h>
#include <stdio.h>
#include "zappy_server_functions.h"

/**
 * to know if the server should end (by SIGINT only)
 */

int end_g = 0;

/**
 * array of functions for every actions
 * @param player the player concerned
 * @param data the struct containing every information about the server
 * @return
 */

const char *(*actions_array_g[12])(player_t *player, data_t *data) = {
	move_forward, turn_right, turn_left, look, inventory, broadcast,
	number_unused_slots, fork_player, eject, take, set, start_incantation};

/**
 * time consumption for every action
 */

const int time_consumption_g[] = {7, 7, 7, 7, 1, 7, 0, 42, 7, 7, 7, 300};

/**
 * existing resources on Trantor
 */

const char *resources_g[] = {"linemate", "deraumere", "sibur", "mendiane",
	"phiras", "thystame", NULL};

/**
 * every command for IA
 */

const char *commands_g[] = {"Forward", "Right", "Left", "Look", "Inventory",
	"Broadcast", "Connect_nbr", "Fork", "Eject", "Take", "Set",
	"Incantation", NULL};

/**
 * needed players and resources for level up
 */

const level_up_t needed_to_level_up_g[LEVEL_MAX] = {{0, {0, 0, 0, 0, 0, 0}},
	{1, {1, 0, 0, 0, 0, 0}}, {2, {1, 1, 1, 0, 0, 0}},
	{2, {2, 0, 1, 0, 2, 0}}, {4, {1, 1, 2, 0, 1, 0}},
	{4, {1, 2, 1, 3, 0, 0}}, {6, {1, 2, 3, 0, 1, 0}},
	{6, {2, 2, 2, 2, 2, 1}}};

/**
 * SIGHANDLER for SIGINT
 * @param signum unused
 */

void sighandler(__attribute__((unused)) int signum)
{
	printf("should end\n");
	end_g = 1;
}

/**
 * get index from a given string in a given global array
 * @param array the array to search in
 * @param to_find the string to find
 * @return the index found, or -1 if was not found
 */

int get_index_global(const char **array, const char *to_find)
{
	int i = 0;

	while (array[i]) {
		if (strcmp(to_find, array[i]) == 0)
			return i;
		i += 1;
	}
	return -1;
}

/**
 * return a unique id, used to create entities
 * @return the unique id
 */

int get_unique_id(void)
{
	static int id = 0;
	int st = id;

	id += 1;
	return st;
}
