/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <memory.h>
#include <math.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"
#include "zappy_server_macros.h"

/**
 * Function that finds the shortest path between 2 points, taking into account
 * the fact that Trantor is toric
 * @param origin the origin point
 * @param dest the dest point
 * @param data the struct containing every information about the server
 * @return
 */

vector_2i_t get_shortest_clone_vector(vector_2i_t *origin, vector_2i_t *dest,
	data_t *data)
{
	static const int pos[9][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
		{0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	float normal_length[9] = {0};
	int i = 0;

	while (i != 9) {
		normal_length[i] = get_normal_length_vectors(origin,
			(vector_2i_t){dest->x + data->size.x * pos[i][0],
				dest->y + data->size.y * pos[i][1]});
		i += 1;
	}
	i = get_smallest_float_index(normal_length, 9);
	return (vector_2i_t){dest->x + data->size.x * pos[i][0] - origin->x,
		dest->y + data->size.y * pos[i][1] - origin->y};
}

/**
 * sends message to a specific player
 * @param broadcaster the player that broadcasts
 * @param listening the player that receives the broadcast
 * @param data the struct containing every information about the server
 */

void broadcast_player(player_t *broadcaster, player_t *listening, data_t *data)
{
	int main_direction = 0;
	char buff[BUFF_SIZE];

	vector_2i_t receiving_vector = get_shortest_clone_vector(
		&broadcaster->cell->pos, &listening->cell->pos, data);
	if (broadcaster->cell == listening->cell) {
		sprintf(buff, "message 0, %s\n",
			broadcaster->tasks.tasks[0].additional_informations);
		listening->should_close += send_to_client(listening->socket_fd,
			buff);
		return;
	}
	main_direction = get_main_direction(&receiving_vector);
	main_direction = apply_rotation_on_direction(main_direction,
		listening->direction);
	sprintf(buff, "message %i, %s\n", main_direction,
		broadcaster->tasks.tasks[0].additional_informations);
	listening->should_close += send_to_client(listening->socket_fd, buff);
}

/**
 * first function called for broadcasting
 * @param player the player that broadcast
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */

const char *broadcast(player_t *player, data_t *data)
{
	player_ll_t *tmp = data->players;

	while (tmp != NULL) {
		if (tmp->player != player)
			broadcast_player(player, tmp->player, data);
		tmp = tmp->next;
	}
	pbc_broadcast(data, player,
		player->tasks.tasks[0].additional_informations);
	return xstrdup("ok\n");
}
