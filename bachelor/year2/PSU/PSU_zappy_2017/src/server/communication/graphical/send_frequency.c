/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include "zappy_server_functions.h"

/**
 * send the frequency of the server to graphical client
 * @param data struct containing informations about server and game
 * @param fd the fd of the graphical client to send the information to
 */

void send_frequency(const data_t *data, const int fd)
{
	char buff[256];

	sprintf(buff, "sgt %i\n", data->timer.delta_size);
	send_to_client(fd, buff);
}
