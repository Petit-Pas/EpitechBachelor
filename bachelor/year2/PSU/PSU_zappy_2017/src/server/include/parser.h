/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#ifndef ZAPPY_PARSER_H
# define ZAPPY_PARSER_H

#include "zappy_server_structs.h"

int get_max_client_in_team(data_t *data, const char **av);
int check_for_help(const char **av);

#endif //ZAPPY_PARSER_H
