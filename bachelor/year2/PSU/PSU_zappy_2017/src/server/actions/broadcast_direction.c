/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include "zappy_server_structs.h"
#include "zappy_server_macros.h"
#include "zappy_server_functions.h"

/**
 * get the slope of a given vector
 * \warning to avoid a division by zero, if x == 0 we return y * 100
 * @param vector the vector tu measure
 * @return the slope of the given vector
 */

float get_slope(const vector_2i_t *vector)
{
	if (vector->y == 0)
		return 0;
	if (vector->x == 0)
		return vector->y * 100;
	return (float)vector->y / (float)vector->x;
}

/**
 * get the result depending on the slope of the given vector (by quadrant)
 * mark[0] = lowest slope
 * mark[1] = highest slope
 * result[0] is when lower than lowest slope
 * result[1] is when between 2 slopes
 * result[2] is when higher than highest slope
 * @param receiving_vector the vector between broadcaster and receiver
 * @param mark the separation of this quadrant
 * @param result the values per separation
 * @return the number wanted by IA client
 */

int calc_result_by_slope(const vector_2i_t *receiving_vector, const float *mark,
	int *result
)
{
	float slope = get_slope(receiving_vector);

	if (slope >= mark[1])
		return result[2];
	if (slope <= mark[0])
		return result[0];
	return result[1];
}

/**
 * get main direction for broadcast
 * @param receiving_vector the vector from broadcaster to listener
 * @return the direction wanted by client
 */

int get_main_direction(const vector_2i_t *receiving_vector)
{
	if (receiving_vector->x >= 0) {
		if (receiving_vector->y >= 0)
			return calc_result_by_slope(receiving_vector,
				(float[]){(float)1 / 3, 3},
				(int[]){3, 2, 1});
		return calc_result_by_slope(receiving_vector,
			(float[]){-3, (float)-1 / 3},
			(int[]){5, 4, 3});
	} else if (receiving_vector->y >= 0)
		return calc_result_by_slope(receiving_vector,
			(float[]){-3, (float)-1 / 3},
			(int[]){1, 8, 7});
	return calc_result_by_slope(receiving_vector,
		(float[]){(float)1 / 3, 3}, (int[]){7, 6, 5});
}

/**
 * apply rotation of the player on the vector found for broadcasting
 * @param main_direction direction of the vector found
 * @param players_rotation direction of the player
 * @return the argument to give to the answer of broadcast
 */

int apply_rotation_on_direction(int main_direction, const int players_rotation)
{
	if (players_rotation == 1) {
		main_direction += 2;
		if (main_direction > 8)
			main_direction = main_direction % 8;
	} else if (players_rotation == 2) {
		main_direction += 4;
		if (main_direction > 8)
			main_direction = main_direction % 8;
	} else if (players_rotation == 3) {
		main_direction += 6;
		if (main_direction > 8)
			main_direction = main_direction % 8;
	}
	return main_direction;
}
