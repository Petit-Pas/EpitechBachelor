/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** Internal functions
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "my_malloc.h"

void my_putchar(char c)
{
	write(1, &c, 1);
}

size_t align(size_t size)
{
	if (size % 8 == 0)
		return size;
	return size + (8 - size % 8);
}

void my_putnbr(int nb)
{
	int debut;
	int fin;
	if (nb < 0) {
		my_putchar('-');
		my_putnbr(-nb);
	} else {
		fin = nb % 10;
		debut = nb / 10;
		if (debut != 0)
			my_putnbr(debut);
		my_putchar((char)(fin + '0'));
	}
}

int put_adress(unsigned long nb)
{
	int to_print;
	unsigned long base;
	char *str = "0123456789";
	base = strlen(str);
	if (nb >= base) {
		to_print = (int)(nb % base);
		nb = (nb - to_print) / base;
		put_adress(nb);
		my_putchar(str[to_print]);
	} else
		my_putchar(str[nb]);
	return (0);
}

void show_alloc_mem(void)
{
	void *ptr = sbrk(0);
	metadata_t *tmp;
	printf("break : %p\n", ptr);
	tmp = head_g;
	while (tmp) {
		if (!tmp->free) {
			printf("%p - %p : %li bytes\n", tmp->data,
				tmp->data + tmp->size, tmp->size);
		}
		tmp = tmp->next;
	}
}
