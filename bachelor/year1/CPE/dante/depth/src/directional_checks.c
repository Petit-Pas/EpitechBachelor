/*
** directional_checks.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Apr 28 09:13:25 2017 Benoit Hoffman
** Last update Tue May  2 13:54:04 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"depth.h"

int		check_up(t_map *map, t_list *list, int id)
{
  if (list->y - 1 >= 0 && map->map[list->y - 1][list->x] == '*')
    if (map->skeletton[list->y - 1][list->x] > id)
      return (1);
  return (0);
}

int		check_down(t_map *map, t_list *list, int id)
{
  if (map->map[list->y + 1] != NULL  && map->map[list->y + 1][list->x] == '*')
    if (map->skeletton[list->y + 1][list->x] > id)
      return (1);
  return (0);
}

int		check_right(t_map *map, t_list *list, int id)
{
  if (map->map[list->y][list->x + 1] != '\n' &&
      map->map[list->y][list->x + 1] == '*')
    if (map->skeletton[list->y][list->x + 1] > id)
      return (1);
  return (0);
}

int		check_left(t_map *map, t_list *list, int id)
{
  if (list->x - 1 >= 0 && map->map[list->y][list->x - 1] == '*')
    if (map->skeletton[list->y][list->x - 1] > id)
      return (1);
  return (0);
}
