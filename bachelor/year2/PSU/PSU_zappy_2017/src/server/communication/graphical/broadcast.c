/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stdio.h>
#include <malloc.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * the function to send broadcast to graphical clients
 * @param data the struct containing every information about the server
 * @param player the player that broadcasts
 * @param message the broadcasted message
 */

void pbc_broadcast(data_t *data, const player_t *player, const char *message)
{
	size_t needed =
		(size_t)snprintf(NULL, 0, "pbc %i %s\n", player->id, message) +
			1;
	char *buffer = xmalloc(needed);

	snprintf(buffer, needed, "pbc %i %s\n", player->id, message);
	send_to_graphical(buffer, &data->graphical);
	free(buffer);
}
