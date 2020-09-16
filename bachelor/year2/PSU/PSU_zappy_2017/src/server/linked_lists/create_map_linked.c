/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** tools to create tore
*/

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"

/**
 * create a new node for toric map
 * @param x x-coordinate
 * @param y y-coordinate
 * @return the newly allocated node
 */

static map_t *create_tor_node(const int x, const int y)
{
	map_t *new = xmalloc(sizeof(map_t));

	memset(new, 0, sizeof(map_t));
	new->food = rand() % FREQUENCE_FOOD;
	for (int i = 0; i != AMOUNT_RESSOURCES; i++) {
		if (rand() % 3 == 0)
			new->resources[i] =
				rand() % (AMOUNT_RESSOURCES - i + 1);
	}
	new->pos.y = y;
	new->pos.x = x;
	return new;
}

/**
 * append a node to a line (use same input twice to close the circle)
 * @param line the line
 * @param new the node to append
 * @return the new line
 */

static map_t *append_to_tor_line(map_t *line, map_t *new)
{
	map_t *tmp = line;

	if (line == NULL)
		return new;
	while (tmp->directions[RIGHT] != NULL)
		tmp = tmp->directions[RIGHT];
	tmp->directions[RIGHT] = new;
	new->directions[LEFT] = tmp;
	return line;
}

/**
 * create a while toric line
 * @param size x-size of the wanted line
 * @param y y-coordinated of the line
 * @return the newly allocated line
 */

static map_t *create_tor_line(const int size, const int y)
{
	map_t *line = NULL;
	map_t *new = NULL;
	int actual_x = 0;

	while (actual_x != size) {
		new = create_tor_node(actual_x, y);
		if (new == NULL)
			return NULL;
		line = append_to_tor_line(line, new);
		actual_x += 1;
	}
	append_to_tor_line(line, line);
	return line;
}

/**
 * link 2 toric lines together(use twice same line to end the toric formation)
 * @param origin should be the 0 0 node
 * @param new_line the new line to append to the toric formation
 */

static void link_tor_lines(map_t *origin, map_t *new_line)
{
	map_t *tmp = origin;
	map_t *tmp_new_line = new_line;
	map_t *st = NULL;

	while (tmp->directions[DOWN] != NULL)
		tmp = tmp->directions[DOWN];
	st = tmp;
	do {
		tmp->directions[DOWN] = tmp_new_line;
		tmp_new_line->directions[UP] = tmp;
		tmp = tmp->directions[RIGHT];
		tmp_new_line = tmp_new_line->directions[RIGHT];
	} while (st != tmp);
}

/**
 * create the toric linked map of the given size
 * @param x wanted x-size
 * @param y wanted y-size
 * @return the newly_allocated map
 */

map_t *create_tor_map(const int x, const int y)
{
	map_t *origin = NULL;
	map_t *new_line = NULL;
	int actual_y = 1;

	if (x == 0 || y == 0)
		return NULL;
	origin = create_tor_line(x, 0);
	while (actual_y != y) {
		new_line = create_tor_line(x, actual_y);
		if (new_line == NULL)
			return NULL;
		link_tor_lines(origin, new_line);
		actual_y += 1;
	}
	link_tor_lines(origin, origin);
	return origin;
}
