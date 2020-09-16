/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stdio.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * dump the map size to a given fd
 * @param data the struct containing every information about the server
 * @param fd the given fd
 */

void dump_map_size(const data_t *data, int fd)
{
	char buf[512];

	sprintf(buf, "msz %i %i\n", data->size.x, data->size.y);
	send_to_client(fd, buf);
}
