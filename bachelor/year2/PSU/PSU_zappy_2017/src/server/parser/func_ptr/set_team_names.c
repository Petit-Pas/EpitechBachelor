/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * check if the given team name already exists
 * @param data the struct containing every information about the server
 * @param name the new name of the team
 * @return -1 if an error occurred, 0 otherwise
 */

static int check_name_used(data_t *data, const char *name)
{
	for (int j = 0; data->teams[j] != NULL; ++j) {
		if (strcmp(data->teams[j]->name, name) == 0) {
			dprintf(2, "Another team as the name '%s'\n", name);
			return -1;
		}
	}
	return 0;
}

/**
 * get the -n values (team names)
 * @param data the struct containing every information about the server
 * @param rest_argv the arguments given to the program
 * @return -1 if an error occurred 1 otherwise
 */

int set_team_names(data_t *data, const char **rest_argv)
{
	int i = 0;
	int nb_team = 0;

	while (rest_argv[i] != NULL && rest_argv[i][0] != '-') {
		if (check_name_used(data, rest_argv[i]) < 0)
			return -1;
		for (nb_team = 0; data->teams[nb_team] != NULL; ++nb_team);
		data->teams = xrealloc(data->teams,
			(nb_team + 2) * sizeof(team_t *));
		data->teams[nb_team] = create_team((char *)rest_argv[i],
			data->max_player_in_team);
		data->teams[nb_team + 1] = NULL;
		i++;
	}
	if (i == 0) {
		dprintf(2, "Invalid number of argument after -n\n");
		return -1;
	}
	return i;
}
