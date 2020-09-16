/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Created by vincent,
*/

#include "circular_buffer.h"

static uint32_t circular_buffer_mask(const uint32_t idx)
{
	return (idx & BUFF_SIZE_MASK);
}

void circular_buf_reset(circular_buffer_t *buffer)
{
	buffer->write_idx = 0;
	buffer->read_idx = 0;
}

void circular_buf_put(circular_buffer_t *buffer, const char data)
{
	buffer->buffer[circular_buffer_mask(buffer->write_idx++)] = data;
}

char circular_buf_get(circular_buffer_t *buffer)
{
	return (buffer->buffer[circular_buffer_mask(buffer->read_idx++)]);
}

uint32_t circular_buf_size_stocked(const circular_buffer_t *buffer)
{
	return (buffer->write_idx - buffer->read_idx);
}
