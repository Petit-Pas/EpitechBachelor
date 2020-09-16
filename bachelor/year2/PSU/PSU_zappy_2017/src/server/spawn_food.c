/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <stdlib.h>
#include "zappy_server_functions.h"

/**
 * function to spawn food randomly on the map
 * @param data a struct containing informations about server and game
 */

void food_spawn(data_t *data)
{
	vector_2i_t pos = {(rand() % (data->size.x + 1)),
		(rand() % (data->size.y + 1))};
	map_t *tmp = data->origin;
	int i = 0;

	while (i != pos.y) {
		tmp = tmp->directions[DOWN];
		i += 1;
	}
	i = 0;
	while (i != pos.x) {
		tmp = tmp->directions[RIGHT];
		i += 1;
	}
	if (tmp->food < 5) {
		tmp->food++;
		bct(data, tmp);
	}
}
