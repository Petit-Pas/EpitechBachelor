/*
** astar.c for dante in /home/angevil124/prog/dante/astar
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue May  2 10:12:49 2017 Benoit Hoffman
** Last update Thu May  4 07:59:00 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"astar.h"

t_list		*get_shortest_not_used(t_list **list)
{
  t_list	*tmp;
  t_list	*to_free;

  tmp = *list;
  while (tmp != NULL)
    {
      if (tmp->used == 0)
	return (tmp);
      to_free = tmp;
      tmp = tmp->next;
      free(to_free);
      *list = tmp;
    }
  return (NULL);
}

int             check_directions(t_list **new, t_list *to_check,
				 t_map *map, int id)
{
  if (check_up(map, to_check, id) == 1)
    if (add_up(map, to_check, id, new) == 84)
      return (84);
  if (check_right(map, to_check, id) == 1)
    if (add_right(map, to_check, id, new) == 84)
      return (84);
  if (check_down(map, to_check, id) == 1)
    if (add_down(map, to_check, id, new) == 84)
      return (84);
  if (check_left(map, to_check, id) == 1)
    if (add_left(map, to_check, id, new) == 84)
      return (84);
  return (0);
}

int		astar(t_map *map, t_list **list, int id)
{
  t_list	*to_actualize;

  to_actualize = get_shortest_not_used(list);
  if (to_actualize == NULL)
    return (1);
  id = map->skeletton[to_actualize->y][to_actualize->x] + 1;
  to_actualize->used = 1;
  if (check_directions(list, to_actualize, map, id) == 84)
    return (84);
  return (0);
}
