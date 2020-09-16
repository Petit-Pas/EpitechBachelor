/*
** resolve.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Apr 28 08:30:34 2017 Benoit Hoffman
** Last update Wed May  3 12:12:06 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"astar.h"

int             contains_start(t_list *list, t_map *map)
{
  t_list        *tmp;

  tmp = list;
  while (tmp != NULL)
    {
      if (tmp->x == map->x && tmp->y == map->y)
        return (1);
      tmp = tmp->next;
    }
  return (0);
}

int		resolve(t_map *map)
{
  t_list	*list;
  int		id;
  int		return_value;

  id = 0;
  list = NULL;
  if (add_list(&list, 0, 0, map) == 84)
    return (84);
  map->skeletton[0][0] = id;
  while (contains_start(list, map) == 0)
    {
      return_value = astar(map, &list, id);
      if (return_value == 84)
	return (84);
    }
  free_list(list);
  return (0);
}
