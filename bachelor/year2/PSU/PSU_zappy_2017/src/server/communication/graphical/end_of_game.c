/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <stdio.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * dumps the end of the game to graphical clients
 * @param graphical the graphical strict found in data_t
 * @param winner the team who has won
 */

void end_of_game(graphical_t *graphical, const team_t *winner)
{
	char buf[512];

	if (winner == NULL)
		return;
	sprintf(buf, "seg %s\n", winner->name);
	send_to_graphical(buf, graphical);
}
