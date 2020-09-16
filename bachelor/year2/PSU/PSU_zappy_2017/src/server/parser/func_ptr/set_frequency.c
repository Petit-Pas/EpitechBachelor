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
 * get the -f value
 * @param data the struct containing every information about the server
 * @param rest_argv the arguments given to the program
 * @return -1 if an error occurred 1 otherwise
 */

int set_frequency(data_t *data, const char **rest_argv)
{
	int frequency;

	if (!rest_argv[0]) {
		dprintf(2, "Invalid number of argument after -f\n");
		return -1;
	}
	frequency = atoi(rest_argv[0]);
	if (frequency < 1) {
		dprintf(2,
			"Invalid reciprocal of time unit for execution"
			" of actions\n");
		return -1;
	}
	data->timer.delta_size = 1000000000 / frequency;
	return 1;
}
