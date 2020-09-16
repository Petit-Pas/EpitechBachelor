/*
** check_end.c for navy in /home/angevil124/prog/PSU/PSU_2016_navy
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed Feb  1 08:12:32 2017 Benoit
** Last update Thu Feb  9 08:14:51 2017 Benoit
*/

#include "navy.h"

int	check_hit(char x, char y, t_map *map)
{
  int	new_x;
  int	new_y;

  my_putchar(x + 16, 1);
  my_putchar(y, 1);
  new_x = (x - 48) * 2;
  new_y = (y - 48) + 1;
  if (map->map_perso[new_y][new_x] >= '2' &&
      map->map_perso[new_y][new_x] <= '5')
    return (my_putstr(": hit\n\n", 1, 1));
  return (my_putstr(": missed\n\n", 1, 0));
}

int	check_completed(char **map)
{
  int	x;
  int	y;
  int	hit;

  x = 2;
  hit = 0;
  while (x <= 16)
    {
      y = 2;
      while (y <= 9)
	{
	  if (map[y][x] == 'x')
	    hit++;
	  y++;
	}
      x++;
    }
  if (hit == 14)
    return (1);
  return (0);
}

int	check_end(t_map *map)
{
  int	win;
  int	loose;

  win = check_completed(map->map_ennemy);
  loose = check_completed(map->map_perso);
  if (win == 1 && loose == 0)
    return (1);
  if (win == 1 && loose == 1)
    return (3);
  if (win == 0 && loose == 1)
    return (2);
  return (0);
}

int	game_is_over(t_map *map)
{
  int	stock;

  stock = check_end(map);
  if (stock == 1)
    return (my_putstr("I won\n", 1, 1));
  if (stock == 2)
    return (my_putstr("Enemy won\n", 1, 1));
  if (stock == 3)
    return (my_putstr("Draw\n", 1, 1));
  return (0);
}
