/*
** error.c for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Dec 13 09:18:39 2016 benoit
** Last update Thu Dec 15 14:55:37 2016 benoit
*/

#include "functions.h"

int	check_map(t_map *map, int x, int y, int boxes)
{
  int	spot;
  int	player;

  spot = 0;
  player = 0;
  while (y < map->row)
    {
      x = 0;
      while (x < my_strlen(map->map[y]))
	{
	  if (map->map[y][x] == 'X')
	    boxes++;
	  if (map->map[y][x] == 'P')
	    player++;
	  if (map->map[y][x] == 'O')
	    spot++;
	  x++;
	}
      y++;
    }
  if (player != 1 || spot < boxes || boxes == 0)
    return (84);
  return (0);
}
