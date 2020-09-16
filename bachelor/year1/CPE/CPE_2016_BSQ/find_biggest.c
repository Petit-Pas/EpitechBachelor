/*
** find_biggest.c for bsq in /home/angevil124/prog/CPE/CPE_2016_BSQ
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec  5 13:49:33 2016 benoit
** Last update Wed Dec 14 10:32:10 2016 benoit
*/

#include "structs.h"

int	is_square(t_map *map, int x, int y)
{
  int	stock_y;
  int	stock_x;

  if (x + map->biggest <= map->columns && y + map->biggest <= map->row)
    {
      stock_y = y;
      stock_x = x;
      while (x != stock_x + map->biggest)
	{
	  y = stock_y;
	  while (y != stock_y + map->biggest)
	    {
	      if (map->map[y][x] == 'o')
		return (0);
	      y++;
	    }
	  x++;
	}
      map->biggest++;
      map->x = stock_x;
      map->y = stock_y;
      is_square(map, stock_x, stock_y);
    }
  else
    return (0);
}

int	find_biggest(t_map *map, int x, int y)
{
  int	check_x;
  int	check_y;

  check_y = 0;
  while (check_y != map->row)
    {
      check_x = 0;
      while (check_x != map->columns)
	{
	  is_square(map, check_x, check_y);
	  check_x++;
	}
      check_y++;
    }
}
