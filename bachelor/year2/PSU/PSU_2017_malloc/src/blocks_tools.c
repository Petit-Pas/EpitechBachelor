/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** Internal functions
*/

#include <stddef.h>
#include "my_malloc.h"

void split_block(metadata_t *first, size_t size)
{
	metadata_t *second = (metadata_t *)((char *)first + size +
		sizeof(metadata_t));
	second->next = first->next;
	first->next = second;
	if (second->next)
		second->next->prev = second;
	second->size = first->size - (size + sizeof(metadata_t));
	first->size = size;
	second->free = 1;
	second->prev = first;
	second->data = second + 1;
}

void *alloc_first(size_t size)
{
	size_t raw_size = size + sizeof(metadata_t);
	size_t to_alloc = get_size_to_alloc(raw_size);
	head_g = sbrk(0);
	if (sbrk(to_alloc) == (void *)-1)
		return NULL;
	head_g->size = to_alloc - sizeof(metadata_t);
	head_g->next = NULL;
	head_g->data = head_g + 1;
	head_g->prev = NULL;
	head_g->free = 0;
	split_block(head_g, align(size));
	unlock_mutex();
	return head_g->data;
}

void *append_new_blocks(metadata_t *last, size_t size)
{
	size_t raw_size = size + sizeof(metadata_t);
	size_t to_alloc = get_size_to_alloc(raw_size);
	metadata_t *new;
	new = sbrk(0);
	if (sbrk(to_alloc) == (void *)-1)
		return NULL;
	new->data = new + 1;
	new->prev = last;
	new->free = 0;
	new->next = NULL;
	new->size = to_alloc - sizeof(metadata_t);
	last->next = new;
	split_block(new, align(size));
	unlock_mutex();
	return new->data;
}

void *fill_block(metadata_t *to_fill, size_t size)
{
	to_fill->free = 0;
	if (to_fill->size > size + sizeof(metadata_t))
		split_block(to_fill, size);
	unlock_mutex();
	return to_fill->data;
}

void merge_blocks(metadata_t *first, metadata_t *second)
{
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	first->size += sizeof(metadata_t) + second->size;
}