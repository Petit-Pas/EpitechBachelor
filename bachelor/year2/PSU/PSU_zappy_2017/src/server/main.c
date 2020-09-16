/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** main_file
*/

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <memory.h>
#include <signal.h>
#include "zappy_server_functions.h"

/**
 * init the main data_t structure
 * @param data the struct containing every information about the server
 * @param argv the command line arguments
 * @return 84 if an error occurred, 0 otherwise
 */

static int init_main_data(data_t *data, const char **argv)
{
	struct timespec time;
	int ret;

	memset(data, 0, sizeof(data_t));
	data->teams = xmalloc(sizeof(team_t *));
	data->teams[0] = NULL;
	ret = parse_args(data, argv);
	if (ret != 0)
		return ret;
	data->origin = create_tor_map(data->size.x, data->size.y);
	clock_gettime(CLOCK_MONOTONIC_RAW, &time);
	data->timer.nano_seconds = (int)time.tv_nsec;
	data->timer.seconds = (int)time.tv_sec;
	return 0;
}

/**
 * clean resources when the server closes
 * @param data the struct containing every information about the server
 */

static void clean_resources(data_t *data)
{
	free_map_linked(data->origin, &data->size);
	free_players(data->players);
	free_teams(data->teams);
	for (int i = 0; i != MAX_PENDING_SIZE && data->pending[i] != 0; i++)
		close(data->pending[i]);
	for (int i = 0; i != data->graphical.amount; i++)
		close(data->graphical.fds[i]);
	free(data->graphical.fds);
	close(data->server_fd);
}

/**
 * get the winning team
 * @param data the struct containing every information about the server
 * @return a pointer to tht winning team, NULL if none won
 */

static team_t *winning_team(const data_t *data)
{
	int i = 0;

	while (data->teams[i] != NULL) {
		if (data->teams[i]->amount_of_max_level_players ==
			AMOUNT_OF_MAX_LEVEL_NEEDED)
			return data->teams[i];
		i += 1;
	}
	return NULL;
}

/**
 * the mina loop of the program, only perform new connections and IA's actions
 * @param data the struct containing every information about the server
 */

static void main_loop(data_t *data)
{
	printf("server ON\n");
	signal(SIGINT, sighandler);
	while (data->is_over == 0 && end_g == 0) {
		check_new_client(data);
		check_pendings(data);
		check_received_data(data);
		if (is_elapsed_time(&data->timer) == 1)
			update_players(data);
		usleep(1);
	}
	end_of_game(&data->graphical, winning_team(data));
}

/**
 * Main symbol
 * @param ac argument count
 * @param av argument values
 * @return 84 if an error occurred, 0 otherwise
 */

int main(__attribute__((unused)) int ac, const char **av)
{
	data_t data;
	int ret;

	srand((unsigned int)getpid());
	ret = init_main_data(&data, av);
	if (ret == 84)
		return 84;
	if (ret == 1)
		return 0;
	data.server_fd = server_creation(data.port);
	if (data.server_fd == -1) {
		dprintf(2, "Could not open socket\n");
		clean_resources(&data);
		return 84;
	}
	main_loop(&data);
	clean_resources(&data);
	return 0;
}
