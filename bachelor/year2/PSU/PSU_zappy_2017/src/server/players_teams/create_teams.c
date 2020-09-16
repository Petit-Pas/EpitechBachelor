/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdlib.h>
#include <string.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * create a team
 * @param team_name the name of the new team
 * @param amount_players the amount of connections accepted for this team
 * @return the newly allocated team
 */

team_t *create_team(const char *team_name, const int amount_players)
{
	team_t *new = xmalloc(sizeof(team_t));

	memset(new, 0, sizeof(team_t));
	new->name = xstrdup(team_name);
	new->amount_of_max_connections = amount_players;
	return new;
}
