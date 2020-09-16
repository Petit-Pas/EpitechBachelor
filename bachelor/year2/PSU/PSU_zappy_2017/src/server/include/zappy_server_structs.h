/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** structs
*/

#ifndef ZAPPY_SERVER_STRUCTS_H_
# define ZAPPY_SERVER_STRUCTS_H_

#include <stdio.h>
#include "zappy_server_defines.h"
#include "circular_buffer.h"

/**
 * \file
 * file containing structs
 */

/**
 * used to store coordinates or vectors
 */
typedef struct vector_2i_s {
	int x; /*!< x-coordinate */
	int y; /*!< y-coordinate */
} vector_2i_t;

/**
 * used to store the a task from a player
 */
typedef struct task_s {
	int task; /*!< the id of the task */
	char *additional_informations; /*!< the additional information
					 needed for the task */
} task_t;

/**
 * Used to store the queue_task of a player
 */
typedef struct queue_tasks_s {
	int size; /*!< the size of the  actual task queue */
	task_t tasks[MAX_QUEUE_SIZE]; /*!< the array of task_t representing
					the task queue */
} queue_tasks_t;

/**
 * one of th cell of the toric linked map
 */
typedef struct map_s {
	struct map_s *directions[4]; /*!< pointers to every cardinal direction */
	struct player_ll_s *players_list; /*!< the list of players on this list */
	struct vector_2i_s pos; /*!< the coordinates of this cell */
	int resources[AMOUNT_RESSOURCES]; /*!< the resources on this cell */
	int food; /*!< the amout of doof on this cell */
} map_t;

/**
 * struct representing the inventory of a player
 */
typedef struct inventory_s {
	int ressources[6]; /*!< the resources in the inventory */
	int food; /*!< the amount of food */
} inventory_t;

/**
 * struct representing a player
 */
typedef struct player_s {
	map_t *cell; /*!< the cell on which the player is */
	inventory_t inventory; /*!< the inventory of the player */
	queue_tasks_t tasks; /*!< the task queue of the player */
	struct team_s *team; /*!< the team of the player */
	int direction; /*!< the direction of the player */
	int level; /*!< the level of the player */
	int time_tic_left; /*!< the amount of frames the player can live without eating */
	int waited_for; /*!< the amount of frames the player has been waiting for */
	int socket_fd; /*!< the socket of the player */
	int id; /*!< id of the player */
	int should_close; /*!< set to 1 if the player has disconnected */
	circular_buffer_t buffer;
} player_t;

/**
 * struct used to create double linked list of players
 */
typedef struct player_ll_s {
	player_t *player; /*!< the player */
	struct player_ll_s *next; /*!< pointer to the next player of the list */
} player_ll_t;

/**
 * struct representing a team
 */
typedef struct team_s {
	char *name; /*!< name of the team */
	player_ll_t *list_players; /*!< list of players in the team */
	player_ll_t *eggs; /*!< list of eggs in the team */
	int amount_of_players; /*!< amount of players connected in this team */
	int amount_of_max_connections; /*!< amount of maximum connections */
	int amount_of_max_level_players; /*!< amount of players who reached max level */
	int has_won; /*!< set to 1 if the team has won */
} team_t;

/**
 * struct used to time actions on Trantor
 */
typedef struct timer_s {
	int seconds; /*!< the second when last is_elapsed_time() returned true */
	int nano_seconds; /*!< same as seconds but with nano seconds */
	int delta_size; /*!< the delta in nanoseconds between 2 frames */
} zappy_timer_t;

/**
 * struct containing every graphical opened connection
 */
typedef struct graphical_s {
	int *fds; /*!< the fds of every graphical client */
	int amount; /*!< the amount of graphical clients */
} graphical_t;

/**
 * struct containing every information about the server and the game
 */
typedef struct data_s {
	map_t *origin; /*!< the theorical 0;0 of the map */
	team_t **teams; /*!< the array of teams */
	player_ll_t *players; /*!< the list of every player */
	struct vector_2i_s size; /*!< the size of the map */
	unsigned int max_player_in_team; /*!< the max players per 
					   team at launch */
	zappy_timer_t timer; /*!< the struct to handle time */
	int is_over; /*!< set to 1 if the game is over */
	int server_fd; /*!< the fd of the socket of the server */
	int port; /*!< the port of the server */
	graphical_t graphical;  /*!< the graphical connections */
	int pending[MAX_PENDING_SIZE]; /*!< the connections that are pending */
} data_t;

/**
 * a struct containning information to know the amount of needed
 * players / resources to level up
 */
typedef struct level_up_s {
	int needed_players; /*!< the amount of players needed */
	int needed_resources[AMOUNT_RESSOURCES]; /*!< the amount of
						   resources needed */
} level_up_t;

/**
 * struct used for errors
 */
typedef struct error_message_s {
	int type; /*!< the type of the error */
	char *content; /*!< content of the error */
} error_message_t;

/**
 * contains informations to level up for every level
 */
extern const level_up_t needed_to_level_up_g[LEVEL_MAX];

/**
 * contains time needed for every action
 */
extern const int time_consumption_g[];

#endif /*ZAPPY_SERVER_STRUCTS_H_*/
