/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Internal functions
*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "parser.h"
#include "func_ptr.h"
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

static int exec_func(data_t *data, const char **av, int *i, int *j)
{
	int ret = 0;
	if (flags_func[*j] != NULL) {
		ret = flags_func[*j](data, &av[++(*i)]);
		if (ret < 0)
			return 84;
		*i += ret;
	} else {
		*i += 2;
	}
	*j = -1;
	return 0;
}

static int check_func(data_t *data, const char **av, int *i, int *j)
{
	if (av[*i] && strcmp(flags[*j], av[*i]) == 0) {
		if (exec_func(data, av, i, j) == 84)
			return 84;
	} else if (av[*i] == NULL) {
		return 0;
	}
	return 1;
}

static int find_func(data_t *data, const char **av, int *i)
{
	int ret = 0;
	for (int j = 0; flags[j]; j++) {
		ret = check_func(data, av, i, &j);
		if (ret != 1)
			return ret;
	}
	return 1;
}

static int check_args(const data_t *data)
{
	if (data->teams[0] == NULL)
		dprintf(2, "Missing team names\n");
	else if (data->port == 0)
		dprintf(2, "Missing port num\n");
	else if (data->size.x <= 0 || data->size.y <= 0
		|| data->size.x > 200 || data->size.y > 200)
		dprintf(2, "Invalid size, try between 1 and 200\n");
	else if (data->timer.delta_size == 0)
		dprintf(2, "Frequency'snt\n");
	else
		return 0;
	return 84;
}

int parse_args(data_t *data, const char **av)
{
	int i = 1;

	if (!check_for_help(av))
		return 1;
	if (get_max_client_in_team(data, av) < 0)
		return 84;
	if (!data->max_player_in_team) {
		dprintf(2, "Invalid number of authorized clients per team\n");
		return 84;
	}
	while (av[i]) {
		int ret = find_func(data, av, &i);
		if (ret == 0)
			break;
		if (ret != 1)
			return ret;
		dprintf(2, "'%s' is not a valid flag\n", av[i]);
		return 84;
	}
	return check_args(data);
}
