/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <memory.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"
#include "zappy_server_macros.h"

/**
 * recursively build the Look answer
 * (going forward, left * level, then right * 2 * level + 1 and forward again)
 * @param player the player that looks
 * @param result the buffer to fill
 * @param level the deep of the call
 * @param middle stock of the middle of the line (to go forward easier)
 * @return
 */
static int add_one_vision_level(const player_t *player, char **result,
	const int level, map_t *middle)
{
	map_t *tmp = middle;
	int i = 0;
	int new_left = GET_LEFT_PLAYER(player);
	int new_right = GET_RIGHT_PLAYER(player);

	while (i != level) {
		tmp = tmp->directions[new_left];
		i += 1;
	}
	i = 0;
	while (i != level * 2 + 1) {
		add_one_cell(tmp, result);
		tmp = tmp->directions[new_right];
		i += 1;
	}
	if (level != player->level)
		add_one_vision_level(player, result, level + 1,
			middle->directions[player->direction]);
	return 0;
}

/**
 * main function called for the Look command
 * @param player the player that looks
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
const char *look(player_t *player, __attribute__((unused))data_t *data)
{
	char *result = xstrdup("[");

	add_one_cell(player->cell, &result);
	add_one_vision_level(player, &result, 1,
		player->cell->directions[player->direction]);
	result = xrealloc(result, strlen(result) + 3);
	result[strlen(result) - 1] = ']';
	strcat(result, "\n");
	return result;
}
