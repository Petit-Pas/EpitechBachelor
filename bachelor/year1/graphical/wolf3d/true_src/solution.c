/*
** solution.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Jan 12 09:58:47 2017 benoit
** Last update Fri Feb  3 13:09:00 2017 Benoit
*/

#include <stdlib.h>
#include "fcts_and_strcts.h"

int	check_up_down(t_map *map, int y, int x)
{
  int	return_value;

  return_value = 0;
  if (map->solution[y][x] >= 0)
    {
      if (y > 0 && map->solution[y - 1][x] == -1
	  || map->solution[y - 1][x] > map->solution[y][x] + 1)
	{
	  map->solution[y - 1][x] = map->solution[y][x] + 1;
	  return_value = 1;
	}
      if (y < map->row && map->solution[y + 1][x] == -1
	  || map->solution[y + 1][x] > map->solution[y][x] + 1)
	{
	  map->solution[y + 1][x] = map->solution[y][x] + 1;
	  return_value = 1;
	}
    }
  return (return_value);
}

int	check_sides(t_map *map, int y, int x)
{
  int	return_value;

  return_value = 0;
  if (map->solution[y][x] >= 0)
    {
      if (x > 1 && map->solution[y][x - 1] == - 1
	  || map->solution[y][x - 1] > map->solution[y][x] + 1)
	{
	  map->solution[y][x - 1] = map->solution[y][x] + 1;
	  return_value = 1;
	}
      if (x < (map->solution[y][0] - 1) && map->solution[y][x + 1] == - 1
	  || map->solution[y][x + 1] > map->solution[y][x] + 1)
	{
	  map->solution[y][x + 1] = map->solution[y][x] + 1;
	  return_value = 1;
	}
    }
  return (return_value);
}

void	put_path(t_map *map)
{
  int	x;
  int	y;
  int	done;

  done = 1;
  while (done == 1)
    {
      done = 0;
      y = 0;
      while (y < map->row)
	{
	  x = 1;
	  while (x <= map->map[y][0])
	    {
	      if (check_sides(map, y, x) == 1)
		done = 1;
	      if (check_up_down(map, y, x) == 1)
		done = 1;
	      x++;
	    }
	  y++;
	}
    }
}

int	**epure_tab(t_map *map, int **solution)
{
  int	x;
  int	y;

  y = 0;
  while (y < map->row)
    {
      x = 1;
      while (x <= map->map[y][0])
	{
	  if (solution[y][x] == 1)
	    solution[y][x] = - 3;
	  else if (solution[y][x] == 2)
	    solution[y][x] = - 1;
	  else if (solution[y][x] == 3)
	    solution[y][x] = 0;
	  else
	    solution[y][x] = - 1;
	  x++;
	}
      y++;
    }
  return (solution);
}

int	**prepare_solution(t_map *map)
{
  int	**result;
  int	y;
  int	x;

  y = 0;
  if (!(result = malloc(sizeof(int*) * map->row)))
    return (NULL);
  while (y < map->row)
    {
      if (!(result[y] = malloc(sizeof(int) * (map->map[y][0] + 1))))
	return (NULL);
      x = 0;
      while (x <= map->map[y][0])
	{
	  result[y][x] = map->map[y][x];
	  x++;
	}
      y++;
    }
  return (epure_tab(map, result));
}
