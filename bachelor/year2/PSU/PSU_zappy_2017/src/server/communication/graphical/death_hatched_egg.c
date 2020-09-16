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
 * function that sends the fact that an egg has rot to graphical client
 * @param egg the egg
 * @param graphical the graphical struct found in data_t
 */

void death_hatched_egg(const player_t *egg, graphical_t *graphical)
{
	char buf[512];
	sprintf(buf, "edi %i\n", egg->id);
	send_to_graphical(buf, graphical);
}
