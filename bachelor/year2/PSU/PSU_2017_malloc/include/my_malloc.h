/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** Internal functions
*/

#ifndef PSU_2017_MALLOC_MY_MALLOC_H
# define PSU_2017_MALLOC_MY_MALLOC_H

#include <stddef.h>
#include <unistd.h>
#include <string.h>

typedef struct metadata_s {
	struct metadata_s *next;
	struct metadata_s *prev;
	size_t size;
	int free;
	void *data;
} metadata_t;

extern metadata_t *head_g;

void *malloc(size_t size);
void *calloc(size_t size, size_t size2);
void free(void *ptr);
void split_block(metadata_t *first, size_t size);
void *alloc_first(size_t size);
void *append_new_blocks(metadata_t *last, size_t size);
void *fill_block(metadata_t *to_fill, size_t size);
void merge_blocks(metadata_t *first, metadata_t *second);
void *realloc(void *ptr, size_t size);
size_t get_size_to_alloc(size_t raw_size);
metadata_t *find_block(size_t size, metadata_t **old);
size_t align(size_t size);
void lock_mutex(void);
void unlock_mutex(void);
void show_alloc_mem(void);

#endif //PSU_2017_MALLOC_MY_MALLOC_H
