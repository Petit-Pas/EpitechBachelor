/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by vincent,
*/

#include <stdbool.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "zappy_server_functions.h"
#include "zappy_server_structs.h"
#include "zappy_server_defines.h"

/**
 * return the paramter of the given command
 * @param str the given command
 * @return a pointer to the start of parameters
 */

char *get_cmd_parameters(const char *str)
{
	char *ret_str = strchr(str, ' ');
	size_t i = 0;

	if (!ret_str)
		return (NULL);
	while (ret_str[i] == ' ')
		i++;
	return &ret_str[i];
}

/**
 * transform a n input command, into a task_t and adds it the player
 * @param player the given player
 * @param input the command to transform
 * @param cmd the id of the given command
 * @return false if the task_queue was full, true otherwise
 */

static bool input_to_task(player_t *player, char *input, const int cmd)
{
	task_t task = {cmd, NULL};

	if (cmd == SET || cmd == TAKE || cmd == BROADCAST) {
		task.additional_informations = xstrdup(
			get_cmd_parameters(input));
	}
	if (push_task(&player->tasks, &task) == -1) {
		send_error_message(TASK_FULL, player->socket_fd);
		free(task.additional_informations);
		return (false);
	}
	return (true);
}

/**
 * interpret an input command for a given player
 * @param player player concerned
 * @param input the input string
 * @return false if an error occurred, true otherwise
 */

bool input_interpreter(player_t *player, char *input)
{
	int cmd = 0;

	if (player->tasks.size == MAX_QUEUE_SIZE) {
		send_error_message(TASK_FULL, player->socket_fd);
		return (false);
	}
	if (!bad_input(input, player->socket_fd) &&
		!bad_command(input, player->socket_fd, &cmd) &&
		input_to_task(player, input, cmd))
		return (true);
	return (false);
}
