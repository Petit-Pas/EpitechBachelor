/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

/**
 * get direction for eject when coming from right
 * (transform internal data into external)
 * @param direction the internal direction
 * @return the external direction
 */

int get_direction_from_right(const int direction)
{
	if (direction == 0)
		return 3;
	if (direction == 3)
		return 1;
	if (direction == 2)
		return 5;
	return 7;
}

/**
 * get direction for eject when coming from left
 * (transform internal data into external)
 * @param direction the internal direction
 * @return the external direction
 */

int get_direction_from_left(const int direction)
{
	if (direction == 0)
		return 7;
	if (direction == 1)
		return 1;
	if (direction == 2)
		return 3;
	return 5;
}

/**
 * get direction for eject when coming from down
 * (transform internal data into external)
 * @param direction the internal direction
 * @return the external direction
 */

int get_direction_from_down(const int direction)
{
	if (direction == 1)
		return 3;
	if (direction == 3)
		return 7;
	if (direction == 2)
		return 5;
	return 1;
}

/**
 * get direction for eject when coming from up
 * (transform internal data into external)
 * @param direction the internal direction
 * @return the external direction
 */

int get_direction_from_up(const int direction)
{
	if (direction == 0)
		return 5;
	else if (direction == 2)
		return 1;
	if (direction == 1)
		return 7;
	return 3;
}
