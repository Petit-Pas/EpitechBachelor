/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * get the -y value
 * @param data the struct containing every information about the server
 * @param rest_argv the arguments given to the program
 * @return -1 if an error occurred 1 otherwise
 */

int set_height(data_t *data, const char **rest_argv)
{
	int height;

	if (!rest_argv[0]) {
		dprintf(2, "Invalid number of argument after -y\n");
		return -1;
	}
	height = atoi(rest_argv[0]);
	if (height <= 0)
		dprintf(2, "Invalid height\n");
	data->size.y = height;
	return 1;
}
