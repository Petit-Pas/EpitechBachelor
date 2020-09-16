/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <stdlib.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * send the main information when a graphical client connects
 * @param data a struct containing informations about server and game
 * @param fd the fd of the new graphical client
 */

static void send_main_informations_graphic(const data_t *data, const int fd)
{
	player_ll_t *tmp = data->players;

	dump_map_size(data, fd);
	dump_all_eggs(data, fd);
	send_frequency(data, fd);
	mct(data, fd);
	tna(data, fd);
	while (tmp != NULL) {
		pnw_one_client(tmp->player, fd);
		tmp = tmp->next;
	}
}

/**
 * add a pendinf connection to the graphical clients, then send
 * it first needed informations
 * @param data the struct containing every information about the server
 * @param index the index of the pending connection to accept
 */

void add_graphical_connection(data_t *data, const int index)
{
	const int fd = data->pending[index];

	data->graphical.fds = xrealloc(data->graphical.fds,
		sizeof(int) * (data->graphical.amount + 1));
	data->graphical.fds[data->graphical.amount] = fd;
	data->graphical.amount += 1;
	send_main_informations_graphic(data, fd);
}
