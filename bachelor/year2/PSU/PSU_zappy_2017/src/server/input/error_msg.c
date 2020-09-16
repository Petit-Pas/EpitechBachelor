/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by vincent,
*/

#include <stdbool.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "zappy_server_defines.h"
#include "zappy_server_structs.h"

/**
 * send an error message to a given client
 * @param type type of the error
 * @param fd_client fd of the client
 * @return true if no error was found, false otherwise
 */

bool send_error_message(int type, const int fd_client)
{
	static const error_message_t msg[] = {
		{TOO_LARGE_MSG, "Error: message too long."},
		{TASK_FULL, "Error: task queue full."},
		{UNKNOWN_COMMAND, "Error: unknown command."},
		{UNKNOWN_OBJECT, "Error: unknown resources."}, {0, NULL}};

	for (int i = 0; msg[i].content; ++i) {
		if (msg[i].type == type &&
			dprintf(fd_client, "%s\n", msg[type].content) < 0)
			return (false);
	}
	return (true);
}

/**
 * send error mess depending on the given command
 * @param type type of the command
 * @param fd_client fd of the client
 * @return false if the command existed, true otherwise
 */

bool send_error_cmd_message(int type, const int fd_client)
{
	static const error_message_t msg[] = {
		{MOVE_FORWARD, "Error: bad Forward command."},
		{TURN_RIGHT, "Error: bad Right command."},
		{TURN_LEFT, "Error: bad Left command."},
		{LOOK, "Error: bad Look command."},
		{INVENTORY, "Error: bad Inventory command."},
		{BROADCAST, "Error: bad Broadcast command."},
		{NUMBER_UNUSED_SLOTS, "Error: bad Connect number command."},
		{FORK, "Error: bad Fork command."}, {EJECT, "Error: bad"
		" Eject command."}, {TAKE, "Error: bad Take command."},
		{SET, "Error: bad Set command."},
		{START_INCANTATION, "Error: bad Incantation command."},
		{0, NULL}};

	for (int i = 0; msg[i].content; ++i) {
		if (msg[i].type == type &&
			dprintf(fd_client, "%s\n", msg[type].content) < 0)
			return (false);
	}
	return (true);
}
