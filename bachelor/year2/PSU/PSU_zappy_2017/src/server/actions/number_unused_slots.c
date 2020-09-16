/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include "zappy_server_functions.h"
#include "zappy_server_macros.h"

/**
 * the main function called for the Connect_nbr command
 * @param player the player that makes the command
 * @param data the struct containing every information about the server
 * @return the answer of the server
 */
const char *number_unused_slots(player_t *player,
	__attribute__((unused))data_t *data)
{
	char *buffer = xmalloc(16);

	sprintf(buffer, "%i\n", AVAILABLE_SLOTS(player));
	return buffer;
}
