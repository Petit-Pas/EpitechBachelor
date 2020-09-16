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
 * the function that dump the fact that an egg has been laid by
 * a player to graphical clients
 * @param player the player concerned
 * @param egg the egg concerned
 * @param graphical the graphical struct found in data_t
 */

void egg_laid(const player_t *player, const player_t *egg,
	graphical_t *graphical)
{
	char buf[512];

	snprintf(buf, 512, "enw %i %s %i %i\n", egg->id, player->team->name,
		player->cell->pos.x, player->cell->pos.y);
	send_to_graphical(buf, graphical);
}

/**
 * dump only one egg, to only one fd
 * @param team_name name of the team who spawned the egg
 * @param fd the fd to send to
 * @param egg the egg
 */

static void dump_egg_one_fd(const char *team_name, const int fd,
	const player_t *egg)
{
	char buf[512];

	snprintf(buf, 512, "enw %i %s %i %i\n", egg->id, team_name,
		egg->cell->pos.x, egg->cell->pos.y);
	send_to_client(fd, buf);
}

/**
 * dump every egg, to only ne fd
 * @param data the struct that contains any information about server and game
 * @param fd the fd to send to
 */

void dump_all_eggs(const data_t *data, const int fd)
{
	player_ll_t *egg;

	for (int i = 0; data->teams[i]; i++) {
		egg = data->teams[i]->eggs;
		while (egg != NULL) {
			dump_egg_one_fd(data->teams[i]->name, fd, egg->player);
			egg = egg->next;
		}
	}
}
