/*
** copy_tab.c for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec 12 12:43:14 2016 benoit
** Last update Thu Dec 15 14:15:47 2016 benoit
*/

#include "functions.h"

void	reset_map(t_map *map)
{
  int	x;
  int	y;

  y = 0;
  while (y < map->row)
    {
      x = 0;
      while (x < my_strlen(map->map[y]))
	{
	  map->map[y][x] = map->map_init[y][x];
	  x++;
	}
      y++;
    }
}
