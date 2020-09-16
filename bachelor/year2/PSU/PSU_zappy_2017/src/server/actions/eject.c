/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <memory.h>
#include "zappy_server_macros.h"
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * get the direction from which the player was ejected, then send this information to the client
 * @param player_pushed the player pushed
 * @param direction_push the direction from which he wwas pushed
 * @param data a struct containing informations about server and game
 */
static void send_eject(player_t *player_pushed, int direction_push,
	data_t *data)
{
	char msg[64];
	int (*array_func[4])(int) = {get_direction_from_right,
		get_direction_from_left, get_direction_from_down,
		get_direction_from_up};

	sprintf(msg, "eject: %i\n",
		array_func[direction_push](player_pushed->direction));
	player_pushed->should_close += send_to_client(player_pushed->socket_fd,
		msg);
	dump_one_player(player_pushed, &data->graphical);
}

/**
 * modify the pointer to the cell in each player of the list to the
 * cell forward player
 * @param player the player that ejects
 * @param data a struct containing informations about server and game
 */
static void move_players_cell(player_t *player, data_t *data)
{
	player_ll_t *tmp = PLAYER_LIST_CELL(player);

	while (tmp != NULL) {
		tmp->player->cell = CELL_FORWARD(player);
		send_eject(tmp->player, player->direction, data);
		tmp = tmp->next;
	}
}

/**
 * main function called for eject command
 * @param player the player that ejects
 * @param data the struct containing every information about the server
 * @return the answer of the server to the command
 */
const char *eject(player_t *player, data_t *data)
{
	if (count_players(player->cell->players_list) == 1)
		return strdup("ko\n");
	dump_player_eject(player, &data->graphical);
	if (player->cell == CELL_FORWARD(player))
		return strdup("ok\n");
	PLAYER_LIST_CELL(player) = remove_player_from_list(
		PLAYER_LIST_CELL(player), player);
	move_players_cell(player, data);
	PLAYER_LIST_CELL_FORWARD(player) = append_to_player_list(
		PLAYER_LIST_CELL_FORWARD(player), PLAYER_LIST_CELL(player));
	PLAYER_LIST_CELL(player) = NULL;
	PLAYER_LIST_CELL(player) = append_to_player_list(
		PLAYER_LIST_CELL(player), create_node_player_list(player));
	dump_players_cell(player->cell->directions[player->direction],
		&data->graphical);
	return xstrdup("ok\n");
}
