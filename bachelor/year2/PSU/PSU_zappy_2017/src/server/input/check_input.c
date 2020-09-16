/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by vincent,
*/

#include <memory.h>
#include "zappy_server_defines.h"
#include "zappy_server_functions.h"

/**
 * find the corresponding task
 * @param string the task
 * @return the index of the task, -1 as an error
 */

int get_task_by_cmp(const char *string)
{
	for (int index = 0; commands_g[index]; ++index) {
		if (!strncmp(commands_g[index], string,
			strlen(commands_g[index])))
			return (index);
	}
	return (-1);
}

/**
 * checks wheter or not the command is an unknown command
 * @param command the command to check
 * @return true if it is, false otherwise
 */

static bool is_unknown_command(const char *command)
{
	if (get_task_by_cmp(command) == -1)
		return (true);
	return (false);
}

/**
 * replace first occurence of a char in a string by another char
 * @param str the string to modify
 * @param occurrence the char to find
 * @param replace the char to put
 */

void replace_first_occurrence_in_str(char *str, const char occurrence,
	const char replace
)
{
	for (int i = 0; str[i]; ++i) {
		if (str[i] == occurrence) {
			str[i] = replace;
			break;
		}
	}
}

/**
 * check the input to see if it is valid
 * @param input the string to check
 * @param fd the fd of the client
 * @return true is so, false otherwise
 */

bool bad_input(char *input, const int fd)
{
	if (strlen(input) > 50010)
		send_error_message(TOO_LARGE_MSG, fd);
	else if (is_unknown_command(input))
		send_error_message(UNKNOWN_COMMAND, fd);
	else {
		replace_first_occurrence_in_str(input, '\n', 0);
		return (false);
	}
	return (true);
}
