/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include "zappy_server_structs.h"

/**
 * get the cell at the given pos
 * @param data the struct containing every information about the server
 * @param x the x-coordinate of the wanted cell
 * @param y the y-coordinate of the wanted cell
 * @return a pointer to the wanted cell
 */

map_t *get_cell_at_pos(const data_t *data, int x, int y)
{
	map_t *tmp = data->origin;
	while (x > 0) {
		tmp = tmp->directions[RIGHT];
		x--;
	}
	while (y > 0) {
		tmp = tmp->directions[DOWN];
		y--;
	}
	return tmp;
}
