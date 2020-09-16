/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "zappy_server_structs.h"
#include "zappy_server_functions.h"

/**
 * concatenates information to a buffer
 * @param to_fill the buffer to fill
 * @param information the information to add
 * @param amount the amount of time information must be added
 */

void add_information_buffer(char **to_fill, const char *information,
	const int amount)
{
	int i = 0;

	while (i != amount) {
		*to_fill = xrealloc(*to_fill,
			strlen(*to_fill) + strlen(information) + 2);
		strcat(*to_fill, information);
		strcat(*to_fill, " ");
		i += 1;
	}
}

/**
 * remove last blank and replace it with a given one
 * @param to_fill the string to modify
 * @param c the character to replace
 */

void replace_last_blank(char **to_fill, char c)
{
	char buf[2];

	*buf = c;
	buf[1] = 0;
	if ((*to_fill)[strlen(*to_fill) - 1] != c) {
		(*to_fill)[strlen(*to_fill) - 1] = c;
		return;
	}
	(*to_fill) = xrealloc(*to_fill, strlen(*to_fill) + 2);
	strcat(*to_fill, buf);
}

/**
 * add the description of the given cell a given buffer
 * @param cell the cell to add
 * @param to_fill the buffer to fill
 * @return 0
 */

int add_one_cell(const map_t *cell, char **to_fill)
{
	int i = 0;

	add_information_buffer(to_fill, "player",
		count_players(cell->players_list));
	add_information_buffer(to_fill, "food", cell->food);
	while (i != AMOUNT_RESSOURCES) {
		add_information_buffer(to_fill, resources_g[i],
			cell->resources[i]);
		i += 1;
	}
	replace_last_blank(to_fill, ',');
	return 0;
}
