/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <stdlib.h>
#include <memory.h>
#include "zappy_server_structs.h"
#include "zappy_server_functions.h"

/**
 * kill a player that has been disconnected (by client itself)
 * @param data the struct containing all the datas about the server and the game
 * @param player the concerned player
 */

static void disconnect_client(data_t *data, player_ll_t **player)
{
	player_ll_t *st = (*player)->next;
	player_dead(*player, data);
	*player = st;
}

void check_received_data(data_t *data)
{
	player_ll_t *tmp = data->players;
	char msg[BUFF_SIZE];

	msg[0] = 0;
	while (tmp) {
		if (!handle_client_request(tmp->player, msg))
			disconnect_client(data, &tmp);
		else if (*msg) {
			input_interpreter(tmp->player, msg);
			msg[0] = 0;
		}
		if (tmp)
			tmp = tmp->next;
	}
}
