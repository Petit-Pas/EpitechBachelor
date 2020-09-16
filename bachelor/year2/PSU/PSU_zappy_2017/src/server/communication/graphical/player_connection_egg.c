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
 * dumps an egg connection
 * @param egg the egg concerned
 * @param graphical the graphical srtruct found in data_t
 */

void player_connection_egg(const player_t *egg, graphical_t *graphical)
{
	char buf[512];
	sprintf(buf, "ebo %i\n", egg->id);
	send_to_graphical(buf, graphical);
}
