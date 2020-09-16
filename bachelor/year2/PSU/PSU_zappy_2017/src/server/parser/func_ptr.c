/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stddef.h>
#include "func_ptr.h"

int (*flags_func[])(data_t *data, const char **rest_argv) =
	{set_port, set_width, set_height, set_team_names, NULL, set_frequency,
		NULL, NULL};

const char *flags[] = {"-p", "-x", "-y", "-n", "-c", "-f", "-help", NULL};