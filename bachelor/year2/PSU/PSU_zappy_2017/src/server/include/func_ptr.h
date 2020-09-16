/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#ifndef ZAPPY_FUNC_PTR_H
# define ZAPPY_FUNC_PTR_H

#include <stddef.h>
#include "zappy_server_structs.h"

int set_clientnb(data_t *data, const char **rest_argv);
int set_frequency(data_t *data, const char **rest_argv);
int set_height(data_t *data, const char **rest_argv);
int set_port(data_t *data, const char **rest_argv);
int set_team_names(data_t *data, const char **rest_argv);
int set_width(data_t *data, const char **rest_argv);

/**
 * array of function for parsing
 * @param data the struct containing all the datas about the server and the game
 * @param rest_argv rest of the arguments
 * @return a random value
 */
extern int (*flags_func[])(data_t *data, const char **rest_argv);

/**
 * list of flags
 */
extern const char *flags[];

#endif //ZAPPY_FUNC_PTR_H
