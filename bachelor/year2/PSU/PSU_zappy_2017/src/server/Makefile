##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Server Makefile
##

CC	=	gcc

RM	=	rm -fv

SRC	=	./input/has_parameter.c								\
		./spawn_food.c									\
		./linked_lists/create_map_linked.c				                \
		./linked_lists/players_linked.c					                \
		./linked_lists/free_linked.c					                \
		./main.c							                            \
		./global.c							                            \
		./tools/maths.c							                        \
		./players_teams/manage_teams.c					                \
		./tools/tools_arrays.c						                    \
		./time_management.c						                        \
		./tools/time_tools.c						                    \
		./players_teams/create_teams.c					                \
		./players_teams/spawn_player.c					                \
		./xlibc.c							                            \
		./players_teams/count_players.c					                \
		./players_teams/player_dead.c					                \
		./players_teams/free_teams.c					                \
		./input/error_msg.c                       			            \
		./input/input_interpreter.c                       		        \
		./input/check_input.c                       			        \
		./input/check_command.c                       			        \
		./actions/broadcast.c						                    \
		./actions/broadcast_direction.c					                \
		./actions/dump_cell.c						                    \
		./actions/fork_player.c						                    \
		./actions/look.c						                        \
		./actions/number_unused_slots.c					                \
		./actions/start_incantation.c					                \
		./actions/turn_left.c						                    \
		./actions/eject.c						                        \
		./actions/get_direction_eject.c					                \
		./actions/inventory.c						                    \
		./actions/move_forward.c					                    \
		./actions/set.c							                        \
		./actions/take.c						                        \
		./actions/turn_right.c						                    \
		./queue_tasks/manipulate_queue_tasks.c				            \
		./parser/first_check/help.c					                    \
		./parser/first_check/max_client.c				                \
		./parser/func_ptr/set_clientnb.c				                \
		./parser/func_ptr/set_frequency.c				                \
		./parser/func_ptr/set_height.c					                \
		./parser/func_ptr/set_port.c					                \
		./parser/func_ptr/set_team_names.c				                \
		./parser/func_ptr/set_width.c					                \
		./parser/parse_args.c						                    \
		./parser/func_ptr.c						                        \
		./circular_buffer/circular_buffer.c						        \
		./circular_buffer/check_circular_buffer.c						\
		./communication/graphical/broadcast.c				            \
		./communication/graphical/dump_rotten_egg.c			            \
		./communication/graphical/dump_player.c				            \
		./communication/graphical/dump_level.c				            \
		./communication/graphical/send_to_graphical.c			        \
		./communication/graphical/bct.c					                \
		./communication/graphical/msz.c					                \
		./communication/graphical/tna.c					                \
		./communication/graphical/get_cell_at_pos.c			            \
		./communication/graphical/dump_player_eject.c			        \
		./communication/graphical/send_info_consume_food.c			        \
		./communication/graphical/dump_incantations.c			        \
		./connection/create_server.c					                \
		./connection/create_client.c					                \
		./connection/client_communication.c				                \
		./connection/client_request.c				                    \
		./connection/handle_new_clients.c				                \
		./connection/validate_connection.c				                \
		./communication/graphical/death_hatched_egg.c			        \
		./communication/graphical/dump_inventory.c			            \
		./communication/graphical/egg_hatch.c				            \
		./communication/graphical/egg_laid.c				            \
		./communication/graphical/egg_laying.c				            \
		./communication/graphical/end_of_game.c				            \
		./communication/graphical/player_connection_egg.c		        \
		./communication/graphical/player_death.c			            \
		./communication/graphical/resource_colleting.c			        \
		./communication/graphical/resource_dropping.c			        \
		./communication/graphical/send_frequency.c			            \
		./tools/append_tools.c						                    \
		./communication/receive_data.c					                \
		./communication/graphical/end_incantation.c			            \
		./communication/graphical/manage_graphical_communications.c	    \
		./communication/graphical/pnw.c

OBJ	=	$(SRC:.c=.o)

NAME	=	zappy_server

CFLAGS	=	-Ofast -W -Wall -Wextra -pedantic -Iinclude

LDFLAGS	=	-lm

all:	$(NAME)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	cp -fv $(NAME) ../../

clean:
	$(RM) $(OBJ)

fclean:  clean
	$(RM) $(NAME)

re:	fclean all
