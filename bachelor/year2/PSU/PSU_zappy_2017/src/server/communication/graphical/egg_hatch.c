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
 * dump hatching of eggs to thet graphical clients
 * @param egg the egg concerned
 * @param graphical the graphical struct found in data_t
 */

void egg_hatch(const player_t *egg, graphical_t *graphical)
{
	char buf[512];
	sprintf(buf, "eht %i\n", egg->id);
	send_to_graphical(buf, graphical);
}
