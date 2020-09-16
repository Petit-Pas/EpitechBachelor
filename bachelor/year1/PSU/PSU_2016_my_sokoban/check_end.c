/*
** check_end.c for my_sokoban.c in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec 12 11:25:26 2016 benoit
** Last update Thu Dec 15 14:23:49 2016 benoit
*/

#include "functions.h"

int	check_win(t_map *map)
{
  int	x;
  int	y;

  y = 0;
  while (y != map->row)
    {
      x = 0;
      while (x != my_strlen(map->map[y]))
	{
	  if (map->map[y][x] == 'X' && map->map_init[y][x] != 'O')
	    return (0);
	  x++;
	}
      y++;
    }
  return (1);
}

int	check_box(t_map *map, int x, int y)
{
  if ((map->map[y + 1][x] == '#' || map->map[y + 1][x] == 'X') &&
      (map->map[y][x + 1] == '#' || map->map[y][x + 1] == 'X'))
    return (3);
  if ((map->map[y - 1][x] == '#' || map->map[y - 1][x] == 'X') &&
      (map->map[y][x + 1] == '#' || map->map[y][x + 1] == 'X'))
    return (3);
  if ((map->map[y + 1][x] == '#' || map->map[y + 1][x] == 'X') &&
      (map->map[y][x - 1] == '#' || map->map[y][x - 1] == 'X'))
    return (3);
  if ((map->map[y - 1][x] == '#' || map->map[y - 1][x] == 'X') &&
      (map->map[y][x - 1] == '#' || map->map[y][x - 1] == 'X'))
    return (3);
  return (0);
}

int	check_loose(t_map *map)
{
  int	x;
  int	y;
  int	error;

  error = 0;
  y = 0;
  while (y != map->row)
    {
      x = 0;
      while (x != my_strlen(map->map[y]))
	{
	  if (map->map[y][x] == 'X')
	    if (check_box(map, x, y) >= 2)
	      error += 1;
	  x++;
	}
      y++;
    }
  if (error == map->amount_of_boxes)
    return (84);
  return (0);
}
