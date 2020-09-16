/*
** add_direction.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Apr 28 09:31:44 2017 Benoit Hoffman
** Last update Fri Apr 28 12:02:46 2017 Benoit Hoffman
*/

#include        "breadth.h"

int		add_up_breadth(t_map *map, t_list *list, int id, t_list **new)
{
  map->skeletton[list->y - 1][list->x] = id;
  if (add_list(new, list->x, list->y - 1))
    return (84);
  return (1);
}

int		add_down_breadth(t_map *map, t_list *list, int id, t_list **new)
{
  map->skeletton[list->y + 1][list->x] = id;
  if (add_list(new, list->x, list->y + 1))
    return (84);
  return (1);
}

int		add_left_breadth(t_map *map, t_list *list, int id, t_list **new)
{
  map->skeletton[list->y][list->x - 1] = id;
  if (add_list(new, list->x - 1, list->y))
    return (84);
  return (1);
}

int		add_right_breadth(t_map *map, t_list *list, int id, t_list **new)
{
  map->skeletton[list->y][list->x + 1] = id;
  if (add_list(new, list->x + 1, list->y))
    return (84);
  return (1);
}
