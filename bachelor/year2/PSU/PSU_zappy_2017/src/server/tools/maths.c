/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <math.h>
#include "zappy_server_structs.h"

/**
 * get the normalized length of a given vector
 * @param origin the origin point
 * @param dest the dest point
 * @return the normalized length
 */

float get_normal_length_vectors(vector_2i_t *origin, vector_2i_t dest)
{
	return sqrtf(powf(dest.x - origin->x, 2) + powf(dest.y - origin->y, 2));
}

/**
 * get smallest float of an array
 * @param array the array
 * @param size the size of the array
 * @return the index of the smallest found
 */

int get_smallest_float_index(const float *array, const int size)
{
	float smallest = array[0];
	int index_smallest = 0;
	int i = 1;

	while (i != size) {
		if (array[i] < smallest) {
			smallest = array[i];
			index_smallest = i;
		}
		i += 1;
	}
	return index_smallest;
}

int get_direction_from_angle(const int angle_degree)
{
	static const int complete_angles[4] = {45, 135, 225, 315};
	int i = 0;

	while (i != 4) {
		if (angle_degree == complete_angles[i])
			return (i + 1) * 2;
		i += 1;
	}
	if (angle_degree > 45 && angle_degree < 135)
		return 3;
	if (angle_degree > 135 && angle_degree < 225)
		return 5;
	if (angle_degree > 225 && angle_degree < 315)
		return 7;
	return 1;
}
