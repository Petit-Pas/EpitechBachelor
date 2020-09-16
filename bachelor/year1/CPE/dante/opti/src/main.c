/*
** main.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Apr 27 07:27:44 2017 Benoit Hoffman
** Last update Fri May 12 07:10:18 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include        "opti.h"

void	free_tab(char **map)
{
  int	i;

  i = 0;
  while (map[i])
    {
      free(map[i]);
      i += 1;
    }
  free(map);
}

int	found_one(t_map map, int x, int y)
{
  if (y - 1 > 0 && map.map[y + 1] && map.map[y - 1][x] == 'X'
      && map.map[y + 1][x] == 'X'
      && (x - 1 > 0 && map.map[y][x + 1] && map.map[y][x - 1] == '*'
	  && map.map[y][x + 1] == '*'))
    return (1);
  if (x - 1 > 0 && map.map[y][x + 1] && map.map[y][x - 1] == 'X'
      && map.map[y][x + 1] == 'X'
      && (y - 1 > 0 && map.map[y + 1] && map.map[y - 1][x] == '*'
	  && map.map[y + 1][x] == '*'))
    return (1);
  return (0);
}

int	is_perfect(t_map map)
{
  int	y;
  int	x;

  y = 0;
  while (map.map[y])
    {
      x = 0;
      while (map.map[y][x])
	{
	  if (map.map[y][x] == 'X')
	    if (found_one(map, x, y) == 1)
	      return (1);
	  x += 1;
	}
      y += 1;
    }
  return (0);
}

int	main(int ac, char **av)
{
  t_map map;
  int	val;

  if (ac != 2)
    return (my_putstr("no input file\n", 2, 84));
  if (get_map(av[1], &map, 0) == 84)
    return (84);
  map.y = map.y - 1;
  map.x = map.x - 2;
  if (map.map[0][0] != '*' || map.map[map.y][map.x] != '*')
    return (my_putstr("no start or end\n", 2, 84));
  val = is_perfect(map);
  free_tab(map.map);
  return (val);
}
