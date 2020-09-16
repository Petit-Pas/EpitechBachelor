/*
** fill_player.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Dec 17 10:39:24 2016 benoit
** Last update Fri Feb  3 13:06:01 2017 Benoit
*/

#include "fcts_and_strcts.h"

int	check_map(t_map *map, int x, int y, int end)
{
  int	player;
  int	column;

  player = 0;
  column = map->map[0][0];
  while (y < map->row)
    {
      x = 1;
      if (map->map[y][0] != column)
	return (84);
      while (x < map->map[y][0])
	{
	  if (map->map[y][x] != 0 && map->map[y][x] != 1
	      && map->map[y][x] != 2 && map->map[y][x] != 3)
	    return (84);
	  if (map->map[y][x] == 3)
	    end++;
	  if (map->map[y][x++] == 2)
	    player++;
	}
      y++;
    }
  if (player != 1 || end == 0)
    return (84);
  return (0);
}

void	find_pos(t_map *map, t_player *player)
{
  int	x;
  int	y;

  y = 0;
  while (y < map->row)
    {
      x = 1;
      while (x < map->map[y][0])
	{
	  if (map->map[y][x] == 2)
	    {
	      player->pos.x = x + 0.5;
	      player->pos.y = y + 0.5;
	      return ;
	    }
	  x++;
	}
      y++;
    }
}

int	check_walls(t_map *map)
{
  int	y;

  y = 1;
  while (y != map->row - 2)
    {
      if (map->map[y][1] != 1 || map->map[y][map->map[y][0]] != 1)
	return (84);
      y++;
    }
  return (0);
}

int	check_border(t_map *map)
{
  int	x;

  x = 1;
  while (x != map->map[0][0] - 1)
    {
      if (map->map[0][x] != 1)
	return (84);
      x++;
    }
  x = 1;
  while (x != map->map[map->row - 1][1])
    {
     if (map->map[map->row - 1][x] != 1)
	return (84);
      x++;
    }
  if (check_walls(map))
    return (84);
  return (0);
}

int	fill_player(t_map *map, t_player *player)
{
  map->solution = NULL;
  map->path_found = NULL;
  if (check_map(map, 0, 0, 0) == 84)
    return (my_put_err("invalid map\n"));
  if (check_border(map) == 84)
    return (my_put_err("invalid map\n"));
  find_pos(map, player);
  player->direction = - 90;
  player->stock.x = - 1;
  player->stock.y = - 1;
  map->solution = prepare_solution(map);
  map->path_found = map_cpy(map, 0, 0);
  if (map->solution == NULL || map->path_found == NULL)
    return (my_put_err("malloc error\n"));
  return (0);
}
