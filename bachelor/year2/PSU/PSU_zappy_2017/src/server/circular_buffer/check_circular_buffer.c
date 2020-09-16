/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Created by vincent,
*/

#include "circular_buffer.h"

bool circular_buf_is_empty(circular_buffer_t *buffer)
{
	return (buffer->write_idx == buffer->read_idx);
}

bool circular_buf_is_full(circular_buffer_t *buffer)
{
	return (circular_buf_size_stocked(buffer) == BUFF_SIZE);
}