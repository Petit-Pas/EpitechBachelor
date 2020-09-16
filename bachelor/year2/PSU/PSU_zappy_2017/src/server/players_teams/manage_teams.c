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
 * add a player in a team
 * @param player the given player
 * @param team the given team
 * @return 0
 */

int add_player_in_team(player_t *player, team_t *team)
{
	team->amount_of_players += 1;
	team->list_players = append_to_player_list(team->list_players,
		create_node_player_list(player));
	player->team = team;
	return 0;
}

/**
 * remove player from a team
 * @param player the player to remove
 */

/**
 * create a new team
 * @param name the name of the team
 * @param size_teams the amount of players that can connect
 * @return the newly allocated team
 */

static team_t *create_new_team(const char *name, const int size_teams)
{
	team_t *new = xmalloc(sizeof(team_t));

	memset(new, 0, sizeof(team_t));
	new->name = (char *)name;
	new->amount_of_max_connections = size_teams;
	return new;
}

/**
 * creates an array of teams
 * @param names the name s of all the teams
 * @param size_teams the amount of teams
 * @return the newly allocated teams array
 */

team_t **create_teams(const char **names, const int size_teams)
{
	team_t **teams = xmalloc(sizeof(team_t *) * (array_size(names) + 1));
	int i = 0;

	memset(teams, 0, sizeof(team_t *) * (array_size(names) + 1));
	while (names[i] != NULL) {
		teams[i] = create_new_team(names[i], size_teams);
		if (teams[i] == NULL)
			return NULL;
		i += 1;
	}
	return teams;
}
