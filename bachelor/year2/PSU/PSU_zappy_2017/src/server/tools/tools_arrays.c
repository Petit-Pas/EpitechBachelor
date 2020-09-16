/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stddef.h>

/**
 * get the size of a given char **
 * @param array the given array
 * @return the size of the given array
 */

int array_size(const char **array)
{
	int i = 0;

	while (array[i])
		i++;
	return i;
}
