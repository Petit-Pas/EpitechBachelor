/*
** get_lines.c for tetris in /home/angevil124/prog/PSU/PSU_2016_tetris/Work_in_progress/benoit
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Mar  2 10:20:52 2017 Benoit
** Last update Thu Mar  2 10:37:01 2017 Benoit
*/

#include <stdlib.h>
#include "tetris.h"

void	get_lines(t_map *map)
{
  int	empty;
  int	x;
  int	y;
  int	found;

  y = 1;
  empty = 0;
  while (map->map[y] != NULL)
    {
      found = 0;
      x = 1;
      while (map->map[y][x] != '#' && found == 0)
	{
	  if (map->map[y][x] != ' ')
	    found = 1;
	  x++;
	}
      if (found != 1)
	empty++;
      y++;
    }
  map->lines_left = empty - 1;
}
