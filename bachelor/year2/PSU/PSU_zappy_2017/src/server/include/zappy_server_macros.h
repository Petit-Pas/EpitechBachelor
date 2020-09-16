/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#ifndef ZAPPY_LINKED_ZAPPY_SERVER_MACROS_H
# define ZAPPY_LINKED_ZAPPY_SERVER_MACROS_H

/**
 * \file
 * file containing macros
 */

/**
 * used to get the player list of the cell forward a player
 */
#define PLAYER_LIST_CELL_FORWARD(player) \
player->cell->directions[(player)->direction]->players_list

/**
 * used to get the player list of the cell of a player
 */
#define PLAYER_LIST_CELL(player) player->cell->players_list

/**
 * used to get the cell forward a player
 */
#define CELL_FORWARD(player) player->cell->directions[(player)->direction]

/**
 * used to get the amount of needed players to level up for a player
 */
#define NEEDED_PLAYERS(player) needed_to_level_up_g[(player)->level].\
	needed_players

/**
 * used to get the amount of needed resources to level up for a player
 */
#define NEEDED_RESOURCES(player) \
needed_to_level_up_g[(player)->level].needed_resources

/**
 * get the direction on the left of a player
 */
#define GET_LEFT_PLAYER(player) \
((player)->direction == 0 ? 3 : (player)->direction - 1)

/**
 * get the direction on the right of a player
 */
#define GET_RIGHT_PLAYER(player) \
((player)->direction == 3 ? 0 : (player)->direction + 1)

/**
 * get the amount of available slots form the team of a given player
 */
#define AVAILABLE_SLOTS(player) (((player)->team->amount_of_max_connections) \
- ((player)->team->amount_of_players))

/**
 * get the absolute value of a number
 */
#define ABS(number) (((number) >= 0) ? (number) : (-(number)))

/**
 * check if this player is at start of an incantation
 */
#define START_OF_INCANTATION(player) ((player)->tasks.tasks[0].task == \
START_INCANTATION && (player)->tasks.tasks[0].additional_informations == \
NULL)

/**
 * get the pos of the first egg of a team
 */
#define POS_EGG(team) team->eggs->player->cell->pos

/**
 * print a string (for debug purpose)
 */
#define DEBUG(mess) printf("%s\n", mess)

#endif //ZAPPY_LINKED_ZAPPY_SERVER_MACROS_H
