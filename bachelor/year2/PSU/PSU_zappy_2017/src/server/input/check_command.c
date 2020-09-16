/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by vincent,
*/

#include <stdbool.h>
#include <memory.h>
#include "zappy_server_functions.h"

/**
 * check if the given object exists
 * @param parameter the string to check
 * @param fd the fd of the client
 * @return true if so, false otherwise
 */

static bool bad_object(const char *parameter, const int fd)
{
	if (parameter && strlen(parameter) >= 4 &&
		(get_index_global(resources_g, parameter) != -1 ||
			!strncmp("food", parameter, 5)))
		return (false);
	send_error_message(UNKNOWN_OBJECT, fd);
	return (true);
}

/**
 * check if the given command has the needed parameter, if not,
 * sends an error message
 * @param input the command line to check
 * @param fd the fd of the client
 * @param cmd_type the tyoe of the command
 * @return true if son false otherwise
 */

static bool bad_command_with_parameter(const char *input, const int fd,
	const int cmd_type
)
{
	if (!has_parameters(input)) {
		send_error_cmd_message(cmd_type, fd);
		return (true);
	}
	if (cmd_type == SET || cmd_type == TAKE)
		return (bad_object(get_cmd_parameters(input), fd));
	return (false);
}

/**
 * check if the command without parameter is fine
 * @param input the command line to check
 * @param fd the fd of the client
 * @param cmd_type the type of the command
 * @return true if so, false otherwise
 */

static bool bad_command_with_no_parameter(char *input, const int fd,
	const int cmd_type
)
{
	if (has_parameters(input)) {
		send_error_cmd_message(cmd_type, fd);
		return (true);
	}
	replace_first_occurrence_in_str(input, ' ', 0);
	if (get_index_global(commands_g, input) == -1) {
		send_error_cmd_message(cmd_type, fd);
		return (true);
	}
	return (false);
}

/**
 * checks if a given command exists or not
 * @param input the given command
 * @param fd  the fd of the client
 * @param cmd_type the type of the found command
 * @return true if so, false otherwise
 */

bool bad_command(char *input, const int fd, int *cmd_type)
{
	*cmd_type = get_task_by_cmp(input);
	if (*cmd_type == -1) {
		send_error_message(UNKNOWN_COMMAND, fd);
		return (true);
	}
	if (*cmd_type == SET || *cmd_type == TAKE || *cmd_type == BROADCAST)
		return (bad_command_with_parameter(input, fd, *cmd_type));
	return (bad_command_with_no_parameter(input, fd, *cmd_type));
}
