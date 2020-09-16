/*
** fill_map.c for navy in /home/angevil124/prog/PSU/PSU_2016_navy
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Jan 30 14:26:09 2017 Benoit
** Last update Wed Feb  1 09:33:21 2017 Benoit
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "navy.h"

int	place_vertical(char *boat, t_map *map, int amount, int forward)
{
  int	x;
  int	from_y;
  int	to_y;

  x = (boat[2] - 48) * 2;
  from_y = (boat[3] - 48) + 1;
  to_y = (boat[6] - 48) + 1;
  if (from_y < to_y)
    forward = 1;
  while (from_y != to_y)
    {
      if (map->map_perso[from_y][x] != '.')
	return (84);
      map->map_perso[from_y][x] = boat[0];
      amount++;
      from_y += forward;
    }
  if (map->map_perso[from_y][x] != '.')
    return (84);
  map->map_perso[from_y][x] = boat[0];
  if (amount + 1 != (boat[0] - 48))
    return (84);
  return (0);
}

int	place_horizontal(char *boat, t_map *map, int amount, int forward)
{
  int	y;
  int	from_x;
  int	to_x;

  y = (boat[3] - 48) + 1;
  from_x = (boat[2] - 48) * 2;
  to_x = (boat[5] - 48) * 2;
  if (from_x < to_x)
    forward = 2;
  while (from_x != to_x)
    {
      if (map->map_perso[y][from_x] != '.')
	return (84);
      map->map_perso[y][from_x] = boat[0];
      amount++;
      from_x += forward;
    }
  if (map->map_perso[y][from_x] != '.')
    return (84);
  map->map_perso[y][from_x] = boat[0];
  if (amount + 1 != (boat[0] - 48))
    return (84);
  return (0);
}

int	place_boats(char **boat, t_map *map)
{
  int	i;

  i = 0;
  while (boat[i] != NULL)
    {
      if (is_in_map(boat[i]) == 84)
	return (84);
      if (boat[i][2] == boat[i][5])
	{
	  if (place_vertical(boat[i], map, 0, - 1) == 84)
	    return (84);
	}
      else if (boat[i][3] == boat[i][6])
	{
	  if (place_horizontal(boat[i], map, 0, -2) == 84)
	    return (84);
	}
      else
	return (84);
      i++;
    }
  return (0);
}

int	check_boat_avanced(char **boat, t_map *map)
{
  purify_boats(boat);
  if (check_boats(boat) == 84)
    return (84);
  if (place_boats(boat, map) == 84)
    return (84);
}

int	fill_map(t_map *map, char *path)
{
  int	fd;
  char	**boat;
  int	i;

  i = 0;
  if ((fd = open(path, O_RDONLY)) == - 1)
    return (my_putstr("Couldn't open the file\n", 2, 84));
  if (!(map->map_ennemy = malloc(sizeof(char *) * 11)))
    return (my_putstr("An error has occured\n", 2, 84));
  if (!(map->map_perso = malloc(sizeof(char *) * 11)))
    return (my_putstr("An error has occured\n", 2, 84));
  if (!(boat = malloc(sizeof(char *) * 5)))
    return (my_putstr("An error has occured\n", 2, 84));
  if (init_map(map->map_perso) == 84 || init_map(map->map_ennemy) == 84)
    return (my_putstr("An error has occured\n", 2, 84));
  while (i != 4)
    boat[i++] = get_next_line(fd);
  boat[i] = NULL;
  if (get_next_line(fd) != NULL)
    return (my_putstr("Invalid boats\n", 2, 84));
  close (fd);
  if (check_boat_avanced(boat, map) == 84)
    return (my_putstr("Invalid boats\n", 2, 84));
  free_tab(boat);
  return (0);
}
