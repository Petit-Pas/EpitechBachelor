/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <memory.h>
#include "zappy_server_functions.h"
#include "zappy_server_macros.h"

/**
 * main function called for Forward command
 * @param player player that moves
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
const char *move_forward(player_t *player, data_t *data)
{
	PLAYER_LIST_CELL(player) = remove_player_from_list(
		PLAYER_LIST_CELL(player), player);
	PLAYER_LIST_CELL_FORWARD(player) = append_to_player_list(
		PLAYER_LIST_CELL_FORWARD(player),
		create_node_player_list(player));
	player->cell = CELL_FORWARD(player);
	dump_one_player(player, &data->graphical);
	return xstrdup("ok\n");
}
