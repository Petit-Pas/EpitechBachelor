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
 * function that dumps the end on an incantation to graphical clients
 * @param cell the cell conerned
 * @param graphical the graphical struct that can be found in  data_t
 * @param ok says if the incantation was a sucess or not
 */

void dump_end_incantation(const map_t *cell, graphical_t *graphical,
	const int ok
)
{
	char buf[512];

	sprintf(buf, "pie %i %i %i\n", cell->pos.x, cell->pos.y, ok);
	send_to_graphical(buf, graphical);
}
