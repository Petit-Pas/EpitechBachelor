/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include "zappy_server_functions.h"

/**
 * dump the rot of an egg for graphical clients
 * @param data struct containing information about the server and game
 * @param egg the egg that has rot
 */

void dump_rotten_egg(data_t *data, const player_t *egg)
{
	char buff[256];

	sprintf(buff, "edi %i\n", egg->id);
	send_to_graphical(buff, &data->graphical);
}
