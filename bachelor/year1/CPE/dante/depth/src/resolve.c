/*
** resolve.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Apr 28 08:30:34 2017 Benoit Hoffman
** Last update Wed May  3 12:41:52 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include        "depth.h"

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

void		free_elem(t_list **list)
{
  t_list	*to_free;

  to_free = *list;
  *list = (*list)->next;
  free(to_free);
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

int		check_all(t_map *map, t_list **list, int id)
{
  if (check_up(map, *list, id) == 1)
    return (add_up(map, list, id));
  else if (check_left(map, *list, id) == 1)
    return (add_left(map, list, id));
  else if (check_down(map, *list, id) == 1)
    return (add_down(map, list, id));
  else if (check_right(map, *list, id) == 1)
    return (add_right(map, list, id));
  return (0);
}

int		resolve_depth(t_map *map, int id)
{
  t_list	*list;
  int		return_value;

  list = NULL;
  if (add_list(&list, map->x, map->y) == 84)
    return (84);
  map->skeletton[map->y][map->x] = id;
  while (list != NULL)
    {
      id += 1;
      if (list->x == 0 && list->y == 0)
	{
	  free_list(list);
	  return (0);
	}
      return_value = check_all(map, &list, id);
      if (return_value == 84)
	return (84);
      if (return_value == 0)
	{
	  id -= 2;
	  free_elem(&list);
	}
    }
  return (0);
}
