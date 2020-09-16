/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <func_ptr.h>
#include <memory.h>
#include "zappy_server_structs.h"

/**
 * get the -c value
 * @param data the struct containing every information about the server
 * @param av the arguments given to the program
 * @return -1 if an error occurred 1 otherwise
 */

int get_max_client_in_team(data_t *data, const char **av)
{
	for (int i = 1; av[i] != NULL; ++i) {
		if (av[i] && strcmp(av[i], "-c") == 0 &&
		set_clientnb(data, &av[i + 1]) < 0) {
			return -1;
		}
	}
	return 1;
}
