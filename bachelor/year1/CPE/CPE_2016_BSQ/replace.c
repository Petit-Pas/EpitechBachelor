/*
** replace.c for bsq in /home/angevil124/prog/CPE/CPE_2016_BSQ
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Dec  6 13:37:09 2016 benoit
** Last update Tue Dec  6 16:08:05 2016 benoit
*/

#include <unistd.h>
#include "functions.h"

void	print_map(t_map *map, char c)
{
  int	i;

  i = 0;
  while (i != map->row)
    {
      write(1, map->map[i], map->columns);
      write(1, &c, 1);
      i++;
    }
}

void	replace(t_map *map)
{
  int	x;
  int	y;

  x = map->x;
  map->biggest--;
  while (x < map->x + map->biggest)
    {
      y = map->y;
      while (y < map->y + map->biggest)
	{
	  map->map[y][x] = 'x';
	  y++;
	}
      x++;
    }
}
