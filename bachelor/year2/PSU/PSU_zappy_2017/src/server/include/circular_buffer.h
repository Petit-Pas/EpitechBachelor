/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Created by vincent,
*/

#ifndef PSU_MYIRC_2017_BUFFER_H
#define PSU_MYIRC_2017_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

static const uint32_t BUFF_SIZE = 65536;
static const uint32_t BUFF_SIZE_MASK = 65535;

typedef struct circular_buffer {
	char buffer[65536];
	uint32_t write_idx;
	uint32_t read_idx;
} circular_buffer_t;

void circular_buf_reset(circular_buffer_t *);
void circular_buf_put(circular_buffer_t *, char);
char circular_buf_get(circular_buffer_t *);
uint32_t circular_buf_size_stocked(const circular_buffer_t *);
bool circular_buf_is_empty(circular_buffer_t *);
bool circular_buf_is_full(circular_buffer_t *);

#endif /* PSU_MYIRC_2017_BUFFER_H */
