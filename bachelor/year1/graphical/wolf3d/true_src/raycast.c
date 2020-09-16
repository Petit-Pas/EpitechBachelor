/*
** raycast.c for bswolf3d in /home/angevil124/prog/graphical/bswolf3d/src
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Dec 15 09:31:44 2016 benoit
** Last update Fri Feb  3 13:08:21 2017 Benoit
*/

#include "fcts_and_strcts.h"

int	check_in_map_raycast(t_map *map, float new_pos_y, float new_pos_x)
{
  if (map->solution[(int)(new_pos_y + 0.05)][(int)(new_pos_x + 0.05)] != - 3 &&
      map->solution[(int)(new_pos_y - 0.05)][(int)(new_pos_x + 0.05)] != - 3 &&
      map->solution[(int)(new_pos_y + 0.05)][(int)(new_pos_x - 0.05)] != - 3 &&
      map->solution[(int)(new_pos_y - 0.05)][(int)(new_pos_x - 0.05)] != - 3)
    return (1);
  return (0);
}

float	raycast(sfVector2f pos, float direction,
		t_map *map, sfVector2i mapSize)
{
  float		result;

  result = 0;
  while (check_in_map_raycast(map, pos.y, pos.x) == 1)
    {
      pos = move_forward(pos, - direction, 0.015, map);
      result += 0.015;
    }
  pos = move_forward(pos, - direction, 0.15, map);
  if (map->map[(int)pos.y][(int)pos.x] == 1)
    map->map[(int)pos.y][(int)pos.x] = 4;
  return (result);
}

  /*
  **while ((int)pos.y >= 0 && (int)pos.x >= 1 && (int)pos.y < mapSize.y &&
  **(int)pos.x < mapSize.x && map->map[(int)pos.y][(int)pos.x] != 1
  **&& map->map[(int)pos.y][(int)pos.x] != 4)
  */
