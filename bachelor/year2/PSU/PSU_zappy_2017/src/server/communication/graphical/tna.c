/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stddef.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * dumps the name of all the teams to a given fd
 * @param data the struct containing all the datas about the server and the game
 * @param fd the given fd
 */

void tna(const data_t *data, const int fd)
{
	char tmp_buff[512];
	char *buf = NULL;

	for (int i = 0; data->teams[i] != NULL; ++i) {
		sprintf(tmp_buff, "tna %s\n", data->teams[i]->name);
		if (buf)
			buf = xrealloc(buf, (int)(strlen(buf) + 128));
		else
			buf = xcalloc(1, 128);
		strcat(buf, tmp_buff);
	}
	send_to_client(fd, buf);
	free(buf);
}
