/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zappy_server_functions.h"

/**
 * get the size of an int, once transformed into a char *
 * @param nb the given number
 * @return the size of the given number
 */

static int get_size_int(int nb)
{
	int size = 0;

	if (nb == 0)
		return 1;
	while (nb != 0) {
		size += 1;
		nb /= 10;
	}
	return size;
}

/**
 * append an int to a string
 * @param str the string to append
 * @param to_append the integer to append
 */

void append_int_to_string(char **str, int to_append)
{
	int size = get_size_int(to_append);

	*str = xrealloc(*str, strlen(*str) + size + 2);
	sprintf(&((*str)[strlen(*str)]), " %i", to_append);
}
