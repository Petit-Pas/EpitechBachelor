/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** Internal functions
*/

#include <pthread.h>
#include <stdlib.h>
#include <memory.h>
#include "my_malloc.h"

metadata_t *head_g = NULL;

void *malloc(size_t size)
{
	metadata_t *prev;
	metadata_t *tmp;
	size = align(size);
	if (!size)
		return NULL;
	lock_mutex();
	if (!head_g) {
		return alloc_first(size);
	}
	tmp = find_block(size, &prev);
	if (!tmp) {
		return append_new_blocks(prev, size);
	} else {
		return fill_block(tmp, size);
	}
}

void free(void *ptr)
{
	metadata_t *tmp;
	if (!ptr || ptr > sbrk(0))
		return;
	tmp = (metadata_t *)ptr - 1;
	if (tmp->data != ptr)
		return;
	lock_mutex();
	tmp->free = 1;
	ptr = tmp->next;
	if (ptr && ((metadata_t *)ptr)->free)
		merge_blocks(tmp, ptr);
	ptr = tmp->prev;
	if (ptr)
		merge_blocks(ptr, tmp);
	unlock_mutex();
}

void *realloc(void *ptr, size_t size)
{
	metadata_t *tmp;
	if (!ptr)
		return malloc(size);
	if (size == 0) {
		free(ptr);
		return NULL;
	}
	tmp = ptr - sizeof(metadata_t);
	if (tmp->size >= size) {
		return ptr;
	}
	void *newptr = malloc(size);
	lock_mutex();
	if (newptr)
		memcpy(newptr, tmp->data, tmp->size);
	unlock_mutex();
	free(ptr);
	return newptr;
}

void *calloc(size_t nmemb, size_t size)
{
	size_t length = nmemb * size;
	void *ptr = malloc(length);
	if (ptr) {
		lock_mutex();
		memset(ptr, 0, length);
		unlock_mutex();
	}
	return ptr;
}
