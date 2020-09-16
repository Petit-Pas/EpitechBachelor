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
 * get the -x values (team names)
 * @param data the struct containing every information about the server
 * @param rest_argv the arguments given to the program
 * @return -1 if an error occurred 1 otherwise
 */
 int set_width(data_t *data, const char **rest_argv)
{
	int width;

	if (!rest_argv[0]) {
		dprintf(2, "Invalid number of argument after -x\n");
		return -1;
	}
	width = atoi(rest_argv[0]);
	if (width <= 0)
		dprintf(2, "Invalid width\n");
	data->size.x = width;
	return 1;
}
