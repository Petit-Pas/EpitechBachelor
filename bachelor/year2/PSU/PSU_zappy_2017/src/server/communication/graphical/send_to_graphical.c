/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <unistd.h>
#include <stdio.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * disconnect and close assoicated fd for a closed graphical connection
 * @param graphical the graphical connection found in data_t
 * @param index the index of the given connection
 */

void disconnect_graphical(graphical_t *graphical, int index)
{
	close(graphical->fds[index]);
	while (index < graphical->amount - 1) {
		graphical->fds[index] = graphical->fds[index + 1];
		index += 1;
	}
	graphical->fds[index] = 0;
	graphical->amount -= 1;
}

/**
 * send a message to every graphical client
 * @param message the given message
 * @param graphical the graphical struct found in data_t
 */

void send_to_graphical(const char *message, graphical_t *graphical)
{
	int i = 0;

	while (i != graphical->amount) {
		if (send_to_client(graphical->fds[i], message) == 1)
			disconnect_graphical(graphical, i);
		else
			i += 1;
	}
}
