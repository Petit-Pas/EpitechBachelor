/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <memory.h>
#include <stdio.h>
#include "zappy_server_structs.h"

/**
 * displays the help
 * @return 0
 */

static int display_help(void)
{
	printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2"
	       " ... -c clientsNb -f freq\n"
	       "\tport is the port number\n"
	       "\twidth is the width of the world\n"
	       "\theight is the height of the world\n"
	       "\tnameX is the name of the team X\n"
	       "\tclientsNb is the number of authorized clients per team\n"
	       "\tfreq is the reciprocal of time unit for execution of"
	       " actions\n");
	return 0;
}

/**
 * check if the help has to be displayed
 * @param av the arguments given to the program
 * @return 0 if the help was displayed, 1 otherwise
 */

int check_for_help(const char **av)
{
	for (int i = 1; av[i] != NULL; ++i) {
		if (av[i] && strcmp(av[i], "-help") == 0) {
			display_help();
			return 0;
		}
	}
	return 1;
}
