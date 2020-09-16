/*
** remove_line.c for tetris.c in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Wed Feb 22 11:28:56 2017 Benoit
** Last update Fri Mar  3 11:05:43 2017 shintaro
*/

#include <stdlib.h>
#include "tetris.h"

void	remove_line(t_map *map, int line)
{
  int	i;
  int	j;

  j = 1;
  i = line;
  while (map->map[line][j] != '#')
    {
      map->map[line][j] = ' ';
      j++;
    }
  while (i != 1)
    {
      j = 1;
      while (map->map[i][j] != '#')
	{
	  map->map[i][j] = map->map[i - 1][j];
	  j++;
	}
      i--;
    }
}

void	check_remove_lines(t_map *map)
{
  int	i;
  int	j;

  i = 1;
  while (map->map[i + 1] != NULL)
    {
      j = 1;
      while (map->map[i][j] != '\0' && map->map[i][j] != ' ')
	j++;
      if (map->map[i][j] == '\0')
	{
	  map->score++;
	  remove_line(map, i);
	  if (map->score % 10 == 0 && map->level < 20)
	    map->level++;
	}
      i++;
    }
}
