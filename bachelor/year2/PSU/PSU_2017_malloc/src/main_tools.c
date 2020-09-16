/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** Internal functions
*/

#include <pthread.h>
#include <unistd.h>
#include "my_malloc.h"

void my_putnbr(int nb);

static pthread_mutex_t mutex_g = PTHREAD_MUTEX_INITIALIZER;

void lock_mutex(void)
{
	pthread_mutex_lock(&mutex_g);
}

void unlock_mutex(void)
{
	pthread_mutex_unlock(&mutex_g);
}

metadata_t *find_block(size_t size, metadata_t **old)
{
	metadata_t *tmp = head_g;
	while (tmp) {
		if (tmp->free && tmp->size > size) {
			return tmp;
		}
		*old = tmp;
		tmp = tmp->next;
	}
	return NULL;
}

size_t get_size_to_alloc(size_t raw_size)
{
	size_t amount = 0;
	while (amount <= raw_size) {
		amount += getpagesize();
	}
	amount += (getpagesize() * 10);
	return align(amount);
}
