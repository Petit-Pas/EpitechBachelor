/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

char *xstrdup(const char *str)
{
	char *result = strdup(str);

	if (result == NULL)
		exit(84);
	return result;
}

void *xmalloc(size_t size)
{
	void *result = malloc(size);

	if (result == NULL)
		exit(84);
	return result;
}

void *xcalloc(size_t nmemb, size_t size)
{
	void *result = calloc(nmemb, size);

	if (result == NULL)
		exit(84);
	return result;
}

void *xrealloc(void *ptr, size_t size)
{
	void *result = realloc(ptr, size);

	if (result == NULL)
		exit(84);
	return result;
}