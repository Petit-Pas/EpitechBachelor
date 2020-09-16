/*
** print_solution.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Apr 28 10:54:55 2017 Benoit Hoffman
** Last update Wed May  3 12:10:21 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"astar.h"

int		find_nearest(int *x, int *y, int to_find, t_map *map)
{
  if (*y - 1 >= 0 && map->skeletton[*y - 1][*x] == to_find)
    *y = *y - 1;
  else if (map->skeletton[*y + 1] != NULL &&
	   map->skeletton[*y + 1][*x] == to_find)
    *y = *y + 1;
  else if (*x - 1 >= 0 && map->skeletton[*y][*x - 1] == to_find)
    *x = *x - 1;
  else if (map->map[*y][*x + 1] != '\n' &&
	   map->skeletton[*y][*x + 1] == to_find)
    *x = *x + 1;
  else
    return (84);
  return (0);
}

int		get_solution(t_map *map)
{
  int		x;
  int		y;
  int		last_id;

  last_id = map->skeletton[map->y][map->x];
  x = map->x;
  y = map->y;
  map->map[y][x] = 'o';
  while (last_id != 0)
    {
      if (find_nearest(&x, &y, last_id - 1, map) == 84)
	return (84);
      map->map[y][x] = 'o';
      last_id--;
    }
  return (0);
}

int		print_solution(t_map *map)
{
  int		y;

  y = 0;
  map->map[y][0] = 'o';
  if (get_solution(map) == 84)
    return (0);
  while (map->map[y] != NULL)
    {
      write(1, map->map[y], map->x + 1);
      free(map->map[y]);
      free(map->skeletton[y]);
      write(1, "\n", 1);
      y += 1;
    }
  free(map->map);
  free(map->skeletton);
  return (0);
}
