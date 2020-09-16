/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#ifndef ZAPPY_LINKED_ZAPPY_SERVER_FUNCTIONS_H
# define ZAPPY_LINKED_ZAPPY_SERVER_FUNCTIONS_H

#include <stdbool.h>
#include "zappy_server_structs.h"

/**
 * \file
 * file containing functions
 */

/*
 * tasks stack related functions
 */
int push_task(queue_tasks_t *queue, task_t *task);
task_t *get_head_queue(queue_tasks_t *queue);
void pop_task(queue_tasks_t *queue);

/*
 * linked lists related functions
 */
map_t *create_tor_map(int x, int y);
void free_map_linked(map_t *origin, const vector_2i_t *size);

player_ll_t *create_node_player_list(player_t *player);
player_ll_t *append_to_player_list(player_ll_t *list, player_ll_t *to_add);
player_ll_t *remove_link_from_player_list(player_ll_t *list,
	player_ll_t *to_remove
);
player_ll_t *remove_player_from_list(player_ll_t *list, player_t *to_remove);
void free_player_list(player_ll_t *list);
int count_players(player_ll_t *list);
int count_players_by_level(player_ll_t *list, int level);

/*
 * Action functions
 */
const char *move_forward(player_t *player, data_t *data);
const char *turn_right(player_t *player, data_t *data);
const char *turn_left(player_t *player, data_t *data);
const char *look(player_t *player, data_t *data);
const char *inventory(player_t *player, data_t *data);
const char *broadcast(player_t *player, data_t *data);
const char *number_unused_slots(player_t *player, data_t *data);
const char *fork_player(player_t *player, data_t *data);
const char *eject(player_t *player, data_t *data);
const char *take(player_t *player, data_t *data);
const char *set(player_t *player, data_t *data);
const char *start_incantation(player_t *player, data_t *data);

/*
 * tools for actions
 */
int add_one_cell(const map_t *cell, char **to_fill);
void broadcast_player(player_t *broadcaster, player_t *listening, data_t *data);
int get_main_direction(const vector_2i_t *receiving_vector);
int apply_rotation_on_direction(int main_direction, int players_rotation);

/*
 * used with global arrays
 */
int get_index_global(const char **array, const char *to_find);
void replace_last_blank(char **to_fill, char c);

/*
 * global array action functions, resources, commands, etc..
 */
extern const char *(*actions_array_g[12])(player_t *player, data_t *data);

extern const char *resources_g[];

extern const char *commands_g[];

extern int end_g;

/*
 * used for directions in eject
 */
int get_direction_from_right(int direction);
int get_direction_from_left(int direction);
int get_direction_from_down(int direction);
int get_direction_from_up(int direction);

/*
 * math
 */
int get_smallest_float_index(const float *array, int size);
float get_normal_length_vectors(vector_2i_t *origin, vector_2i_t dest);
int get_direction_from_angle(int angle_degree);

/*
 * array tools
 */
int array_size(const char **array);

/*
 * handle teams
 */
int add_player_in_team(player_t *player, team_t *team);
team_t *create_team(const char *team_name, int amount_players);
player_t *spawn_player(const char *team_name, data_t *data, int x, int y);
team_t *get_team(team_t **teams, const char *team_name);

/*
 * xlibc
 */
char *xstrdup(const char *str);
void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);
void *xcalloc(size_t nmemb, size_t size);

/*
 * loop of time
 */
void player_dead(player_ll_t *player, data_t *data);
int is_elapsed_time(zappy_timer_t *timer);
void update_players(data_t *data);

/*
 * miscelaneous
 */
void free_players(player_ll_t *players);
void free_teams(team_t **teams);
void free_tasks(task_t *tasks);
int get_unique_id(void);
void sighandler(int signum);
void send_to_graphical(const char *message, graphical_t *graphical);
void append_int_to_string(char **str, int to_append);
void food_spawn(data_t *data);
bool has_parameters(const char *string);

/*
 * parsing
 */
int parse_args(data_t *data, const char **av);

/*
 * graphical client
 */
void dump_players_cell(const map_t *cell, graphical_t *graphical);
void dump_one_player(const player_t *player, graphical_t *graphical);
map_t *get_cell_at_pos(data_t *data, int x, int y);
void bct(data_t *data, const map_t *map);
void mct(const data_t *data, int fd);
void tna(const data_t *data, int fd);
void dump_new_player(data_t *data, const player_t *player);
void pnw_one_client(const player_t *player, int fd);
void pbc_broadcast(data_t *data, const player_t *player, const char *message);
void dump_level(const player_t *player, graphical_t *graphical);
void dump_player_eject(const player_t *player, graphical_t *graphical);
void dump_start_incantation(const player_t *player, graphical_t *graphical);
void death_hatched_egg(const player_t *egg, graphical_t *graphical);
void egg_hatch(const player_t *egg, graphical_t *graphical);
void dump_inventory(const player_t *player, graphical_t *graphical);
void egg_laid(const player_t *player, const player_t *egg,
	graphical_t *graphical);
void egg_laying(const player_t *player, graphical_t *graphical);
void dump_end_incantation(const map_t *cell, graphical_t *graphical, int ok);
void end_of_game(graphical_t *graphical, const team_t *winner);
void player_connection_egg(const player_t *egg, graphical_t *graphical);
void player_death(const player_t *player, graphical_t *graphical);
void resource_collecting(const player_t *player, graphical_t *graphical,
	int resource_number);
void resource_dropping(const player_t *player, graphical_t *graphical,
	int resource_number
);
void add_graphical_connection(data_t *data, int index);
void dump_map_size(const data_t *data, int fd);
void dump_all_eggs(const data_t *data, int fd);
void send_frequency(const data_t *data, int fd);
void dump_rotten_egg(data_t *data, const player_t *egg);
void send_info_consume_food(player_t *player, graphical_t *graphical);

/*
 * server connection
 */
int server_creation(int port);
int add_client(int fd);
bool handle_new_client_request(int fd, char *buffer);
bool handle_client_request(player_t *player, char *buffer);
int send_to_client(int fd, const char *msg);
int server();
void try_to_spawn_player(data_t *data, char *team_name, int index);
void check_new_client(data_t *data);
void check_pendings(data_t *data);
void check_received_data(data_t *data);

/*
 * error message
 */
bool send_error_message(int type, int fd_client);
bool send_error_cmd_message(int type, int fd_client);

/*
 * interpret client input
 */
bool input_interpreter(player_t *player, char *input);
bool bad_input(char *input, int fd);
bool bad_command(char *input, int fd, int *cmd_type);
char *get_cmd_parameters(const char *string);
int get_task_by_cmp(const char *string);
void replace_first_occurrence_in_str(char *string, char occurrence,
	char replace
);

#endif //ZAPPY_LINKED_ZAPPY_SERVER_FUNCTIONS_H
