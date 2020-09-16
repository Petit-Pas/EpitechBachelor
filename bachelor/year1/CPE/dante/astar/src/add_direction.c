/*
** add_direction.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Apr 28 09:31:44 2017 Benoit Hoffman
** Last update Tue May  2 12:35:08 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"astar.h"

int		add_up(t_map *map, t_list *list, int id, t_list **new)
{
  map->skeletton[list->y - 1][list->x] = id;
  if (add_list(new, list->x, list->y - 1, map))
    return (84);
  return (1);
}

int		add_down(t_map *map, t_list *list, int id, t_list **new)
{
  map->skeletton[list->y + 1][list->x] = id;
  if (add_list(new, list->x, list->y + 1, map))
    return (84);
  return (1);
}

int		add_left(t_map *map, t_list *list, int id, t_list **new)
{
  map->skeletton[list->y][list->x - 1] = id;
  if (add_list(new, list->x - 1, list->y, map))
    return (84);
  return (1);
}

int		add_right(t_map *map, t_list *list, int id, t_list **new)
{
  map->skeletton[list->y][list->x + 1] = id;
  if (add_list(new, list->x + 1, list->y, map))
    return (84);
  return (1);
}
