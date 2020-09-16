/*
** unperfect.c for dante in /home/angevil124/prog/CPE/dante
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Apr 27 06:44:50 2017 Benoit Hoffman
** Last update Thu Apr 27 07:19:14 2017 Benoit Hoffman
*/

#include	<stdlib.h>

static int	find_horizontal(char **map, int x, int y)
{
  if (x - 1 >= 0 && map[y][x + 1] != '\0')
    {
      if (map[y][x - 1] == 'X' && map[y][x + 1] == 'X')
	return (1);
    }
  return (0);
}

static int	find_vertical(char **map, int x, int y)
{
  if (y - 1 >= 0 && map[y + 1] != NULL)
    {
      if (map[y - 1][x] == 'X' && map[y + 1][x] == 'X')
	return (1);
    }
  return (0);
}

static void	check_if_breakable(char **map, int x, int y)
{
  int		vertical;
  int		horizontal;

  vertical = find_vertical(map, x, y);
  horizontal = find_horizontal(map, x, y);
  if (vertical + horizontal == 1)
    map[y][x] = '*';
}

void		do_unperfect(char **map)
{
  int		x;
  int		y;

  y = 0;
  while (map[y] != NULL)
    {
      x = 0;
      while (map[y][x] != '\0')
	{
	  if (map[y][x] == 'X')
	    check_if_breakable(map, x, y);
	  x += 1;
	}
      y += 1;
    }
}
