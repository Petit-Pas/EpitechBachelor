/*
** put_new_list.c for dante in /home/angevil124/prog/CPE/dante/breadth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Apr 28 11:43:24 2017 Benoit Hoffman
** Last update Wed May  3 12:36:42 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include        "breadth.h"

int             check_directions(t_list **new, t_list *to_check,
				 t_map *map, int id)
{
  if (check_up(map, to_check, id) == 1)
    if (add_up_breadth(map, to_check, id, new) == 84)
      return (84);
  if (check_right(map, to_check, id) == 1)
    if (add_right_breadth(map, to_check, id, new) == 84)
      return (84);
  if (check_down(map, to_check, id) == 1)
    if (add_down_breadth(map, to_check, id, new) == 84)
      return (84);
  if (check_left(map, to_check, id) == 1)
    if (add_left_breadth(map, to_check, id, new) == 84)
      return (84);
  return (0);
}

int		put_new_list(t_list **new, t_list *old, t_map *map, int id)
{
  t_list	*tmp;

  tmp = old;
  while (tmp != NULL)
    {
      check_directions(new, tmp, map, id);
      tmp = tmp->next;
    }
  return (0);
}
