/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** internal functions
*/

#include <stdbool.h>

static bool end_has_parameters(const char *string, int i)
{
	while (string[i] == ' ')
		i++;
	return ((string[i]) ? (true) : (false));
}

/**
 * check wether or not a command has parameter
 * @param string the string to check
 * @return true if so, false otherwise
 */

bool has_parameters(const char *string)
{
	for (int i = 0; string[i]; ++i) {
		if (string[i] == ' ') {
			return end_has_parameters(string, i);
		}
	}
	return (false);
}
