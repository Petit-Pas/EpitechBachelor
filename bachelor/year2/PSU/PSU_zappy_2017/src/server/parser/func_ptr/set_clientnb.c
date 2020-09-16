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
 * get the -c value
 * @param data the struct containing every information about the server
 * @param rest_argv the arguments given to the program
 * @return -1 if an error occurred 1 otherwise
 */

int set_clientnb(data_t *data, const char **rest_argv)
{
	int clientnb;

	if (!rest_argv[0]) {
		dprintf(2, "Invalid number of argument after -c\n");
		return -1;
	}
	clientnb = atoi(rest_argv[0]);
	if (clientnb < 1)
		dprintf(2, "Invalid number of authorized clients per team\n");
	data->max_player_in_team = (unsigned int)clientnb;
	return 1;
}
