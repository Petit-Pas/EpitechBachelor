/*
** manage_map.c for navy in /home/angevil124/prog/PSU/PSU_2016_navy
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Jan 31 10:32:00 2017 Benoit
** Last update Fri Feb 10 11:50:52 2017 Benoit
*/

#include <stdlib.h>
#include "navy.h"

void	my_put_piece(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == 'x')
	put_cross();
      else if (str[i] == 'o')
	put_circle();
      else
	my_putchar(str[i], 1);
      i++;
    }
  my_putchar('\n', 1);
}

void	print_maps(t_map *map)
{
  int	i;

  i = 0;
  my_putstr("my positions:\n", 1, 0);
  while (map->map_perso[i] != NULL)
    {
      my_put_piece(map->map_perso[i]);
      i++;
    }
  my_putstr("\nenemy's positions:\n", 1, 0);
  i = 0;
  while (map->map_ennemy[i] != NULL)
    {
      my_put_piece(map->map_ennemy[i]);
      i++;
    }
  my_putstr("\n", 1, 0);
}

void	put_shot_enemy(char x, char y, t_map *map, int touched)
{
  int	new_x;
  int	new_y;

  new_x = (x - 64) * 2;
  new_y = (y - 48) + 1;
  if (map->map_ennemy[new_y][new_x] == '.')
    {
      if (touched == 0)
	map->map_ennemy[new_y][new_x] = 'o';
      else
	map->map_ennemy[new_y][new_x] = 'x';
    }
}

void	put_shot_perso(char x, char y, t_map *map)
{
  int	new_x;
  int	new_y;

  new_x = (x - 48) * 2;
  new_y = (y - 48) + 1;
  if (map->map_perso[new_y][new_x] == 'o' ||
      map->map_perso[new_y][new_x] == '.')
    map->map_perso[new_y][new_x] = 'o';
  else
    map->map_perso[new_y][new_x] = 'x';
}
