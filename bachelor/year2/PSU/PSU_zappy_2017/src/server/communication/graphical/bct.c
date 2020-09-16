/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include "zappy_server_functions.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

/**
 * dump a tile to the graphical clients
 * @param data the struct containing every information about the server
 * @param tmp the tile to display
 */

void bct(data_t *data, const map_t *tmp)
{
	char buf[512];

	sprintf(buf, "bct %i %i %i %i %i %i %i %i %i\n", tmp->pos.x, tmp->pos.y,
		tmp->food, tmp->resources[LINEMATE], tmp->resources[DERAUMERE],
		tmp->resources[SIBUR], tmp->resources[MENDIANE],
		tmp->resources[PHIRAS], tmp->resources[THYSTAME]);
	send_to_graphical(buf, &data->graphical);
}

/**
 * function that concatenates tiles for graphical client
 * @param tmp the tile to dump
 * @param buf the buffer to increase
 * @return the newly allocated buffer
 */

static char *mct_append(const map_t *tmp, char *buf)
{
	char tmp_buff[512];
	if (buf)
		buf = xrealloc(buf, strlen(buf) + 128);
	else
		buf = xcalloc(1, 128);
	sprintf(tmp_buff, "bct %i %i %i %i %i %i %i %i %i\n", tmp->pos.x,
		tmp->pos.y, tmp->food, tmp->resources[LINEMATE],
		tmp->resources[DERAUMERE], tmp->resources[SIBUR],
		tmp->resources[MENDIANE], tmp->resources[PHIRAS],
		tmp->resources[THYSTAME]);
	strcat(buf, tmp_buff);
	return buf;
}

/**
 * dump the content of the whole map (for display client)
 * @param data  the struct containing every information about the server
 * @param fd the fd to send on
 */

void mct(const data_t *data, const int fd)
{
	map_t *tmp = data->origin;
	map_t *stock_start_line = tmp;
	char *buf = NULL;

	do {
		do {
			buf = mct_append(tmp, buf);
			tmp = tmp->directions[RIGHT];
		} while (stock_start_line != tmp);
		stock_start_line = stock_start_line->directions[DOWN];
		tmp = stock_start_line;
	} while (stock_start_line != data->origin);
	send_to_client(fd, buf);
	free(buf);
}
