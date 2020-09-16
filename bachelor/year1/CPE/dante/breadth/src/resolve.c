/*
** resolve.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Apr 28 08:30:34 2017 Benoit Hoffman
** Last update Tue May  2 11:32:44 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include        "breadth.h"

void		free_list(t_list *list)
{
  t_list	*to_free;
  t_list	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      to_free = tmp;
      tmp = tmp->next;
      free(to_free);
    }
}

int		add_list(t_list **list, int x, int y)
{
  t_list	*new;

  new = malloc(sizeof(*new));
  if (new == NULL)
    return (84);
  new->x = x;
  new->y = y;
  new->next = *list;
  *list = new;
  return (0);
}

int		contains_start(t_list *list)
{
  t_list	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      if (tmp->x == 0 && tmp->y == 0)
	return (1);
      tmp = tmp->next;
    }
  return (0);
}

int		resolve(t_map *map)
{
  t_list	*new;
  t_list	*old;
  int		id;

  id = 0;
  old = NULL;
  new = NULL;
  if (add_list(&new, map->x, map->y) == 84)
    return (84);
  map->skeletton[map->y][map->x] = 0;
  while (contains_start(new) == 0)
    {
      id += 1;
      free_list(old);
      old = new;
      new = NULL;
      if (put_new_list(&new, old, map, id) == 84)
	return (84);
    }
  free_list(old);
  free_list(new);
  return (0);
}
