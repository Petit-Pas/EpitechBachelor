/*
** manage_list.c for dante in /home/angevil124/prog/dante/astar
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed May  3 12:11:23 2017 Benoit Hoffman
** Last update Tue May  9 08:42:50 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"astar.h"

void            free_list(t_list *list)
{
  t_list        *to_free;
  t_list        *tmp;

  tmp = list;
  while (tmp != NULL)
    {
      to_free = tmp;
      tmp = tmp->next;
      free(to_free);
    }
}

void            free_elem(t_list **list)
{
  t_list        *to_free;

  to_free = *list;
  *list = (*list)->next;
  free(to_free);
}

int            insert_list(t_list **list, t_list *to_insert, t_list *tmp)
{
  t_list        *stock;

  stock = *list;
  tmp = (*list)->next;
  if (to_insert->distance <= stock->distance)
    {
      *list = to_insert;
      to_insert->next = stock;
      return (0);
    }
  while (tmp != NULL)
    {
      if (to_insert->distance <= tmp->distance &&
          to_insert->distance >= stock->distance)
	{
          stock->next = to_insert;
          to_insert->next = tmp;
          return (0);
	}
      stock = tmp;
      tmp = tmp->next;
    }
  stock->next = to_insert;
  to_insert->next = NULL;
  return (0);
}

int             add_list(t_list **list, int x, int y, t_map *map)
{
  t_list        *new;

  new = malloc(sizeof(*new));
  if (new == NULL)
    return (84);
  new->x = x;
  new->y = y;
  new->used = 0;
  new->distance = ((map->x - x) * (map->x - x))
    + ((map->y - y) * (map->y - y));
  if (*list != NULL)
    insert_list(list, new, NULL);
  else
    {
      new->next = *list;
      *list = new;
    }
  return (0);
}
