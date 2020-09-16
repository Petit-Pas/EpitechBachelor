/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#ifndef ZAPPY_LINKED_ZAPPY_SERVER_DEFINES_H
# define ZAPPY_LINKED_ZAPPY_SERVER_DEFINES_H

/**
 * \file
 * File containing useful defines
 */

/**
 * The size of the pending connection list
 */
#define MAX_PENDING_SIZE 1024

/**
 * The amount of command the server accepts from clients before ignoring it
 */
#define MAX_QUEUE_SIZE 10

/**
 * the amount of resources on Trantor
 */
#define AMOUNT_RESSOURCES 6

/**
 * the frequence at which food spawns
 */
#define FREQUENCE_FOOD 4

/**
 * the amount of time unit a food gives
 */
#define FOOD_VALUE 126

/**
 * the max level to reach
 */
#define LEVEL_MAX 8

/**
 * The time before an eggs hatches
 */
#define HATCHING_TIME 600

/**
 * The amount of max level players needed to win
 */
#define AMOUNT_OF_MAX_LEVEL_NEEDED 6

/**
 * all the possible directions
 */
enum directions {
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

/**
 * all the existing resources on Trantor
 */
enum resources {
	LINEMATE = 0,
	DERAUMERE = 1,
	SIBUR = 2,
	MENDIANE = 3,
	PHIRAS = 4,
	THYSTAME = 5
};

/**
 * all the possibles tasks that clients can do
 */
enum tasks {
	MOVE_FORWARD = 0,
	TURN_RIGHT = 1,
	TURN_LEFT = 2,
	LOOK = 3,
	INVENTORY = 4,
	BROADCAST = 5,
	NUMBER_UNUSED_SLOTS = 6,
	FORK = 7,
	EJECT = 8,
	TAKE = 9,
	SET = 10,
	START_INCANTATION = 11,
	NONE
};

/**
 * Errors
 */
typedef enum {
	TOO_LARGE_MSG = 0,
	TASK_FULL = 1,
	UNKNOWN_COMMAND = 2,
	UNKNOWN_OBJECT = 3,
} type_error;

#endif //ZAPPY_LINKED_ZAPPY_SERVER_DEFINES_H
