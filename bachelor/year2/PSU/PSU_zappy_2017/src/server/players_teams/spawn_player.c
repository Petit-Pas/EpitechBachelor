/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <string.h>
#include <stdlib.h>
#include "zappy_server_structs.h"
#include "zappy_server_functions.h"

/**
 * create a new player
 * @return the newly allocated player
 */

player_t *create_player(void)
{
	player_t *new = xmalloc(sizeof(player_t));

	memset(new, 0, sizeof(player_t));
	new->id = get_unique_id();
	return new;
}

/**
 * get the team by team name
 * @param teams teams_t array
 * @param team_name the team name we are looking for
 * @return the found team
 */

team_t *get_team(team_t **teams, const char *team_name)
{
	int i = 0;

	while (teams[i] != NULL) {
		if (strcmp(teams[i]->name, team_name) == 0)
			return teams[i];
		i += 1;
	}
	return NULL;
}

/**
 * add a player on map, depending on given position
 * @param new_player the given player
 * @param origin the 0, 0 of the map
 * @param x x-coordinate
 * @param y y-coordinate
 */

static void add_player_on_map(player_t *new_player, map_t *origin, const int x,
	const int y)
{
	map_t *tmp = origin;
	int i = 0;

	while (i != y) {
		tmp = tmp->directions[DOWN];
		i += 1;
	}
	i = 0;
	while (i != x) {
		tmp = tmp->directions[RIGHT];
		i += 1;
	}
	tmp->players_list = append_to_player_list(tmp->players_list,
		create_node_player_list(new_player));
	new_player->cell = tmp;
}

/**
 * spawn a new player at a given position on the map
 * @param team_name the name of the team of the player
 * @param data the struct containing every information about the server
 * @param x x-coordinate of the player
 * @param y y-coordinate of the player
 * @return the newly created player
 */

player_t *spawn_player(const char *team_name, data_t *data, const int x,
	const int y)
{
	player_t *new = create_player();

	new->level = 1;
	new->direction = rand() % 4;
	new->inventory.food = 10;
	add_player_in_team(new, get_team(data->teams, team_name));
	add_player_on_map(new, data->origin, x, y);
	data->players = append_to_player_list(data->players,
		create_node_player_list(new));
	return new;
}
