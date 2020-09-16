/*
** map_cpy.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Jan 12 12:41:44 2017 benoit
** Last update Fri Feb  3 13:06:35 2017 Benoit
*/

#include <stdlib.h>
#include "fcts_and_strcts.h"

int	**map_cpy(t_map *map, int x, int y)
{
  int	**new_map;

  new_map = malloc(sizeof(int *) * map->row);
  if (new_map == NULL)
    return (NULL);
  while (y < map->row)
    {
      x = 0;
      if (!(new_map[y] = malloc(sizeof(int) * (map->map[y][0] + 1))))
	return (NULL);
      while (x <= map->map[y][0])
	{
	  if (map->map[y][x] == 1)
	    new_map[y][x] = - 3;
	  else if (map->map[y][x] == 2)
            new_map[y][x] = - 1;
          else if (map->map[y][x] == 3)
            new_map[y][x] = 0;
          else
            new_map[y][x] = - 1;
	  x++;
	}
      y++;
    }
  return (new_map);
}
