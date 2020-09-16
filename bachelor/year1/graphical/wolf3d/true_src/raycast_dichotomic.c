/*
** raycast.c for bswolf3d in /home/angevil124/prog/graphical/bswolf3d/src
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Dec 15 09:31:44 2016 benoit
** Last update Mon Jan  2 10:37:12 2017 benoit
*/

#include "./include/fcts_and_strcts.h"

float	raycast(sfVector2f pos, float direction,
		t_map *map, sfVector2i mapSize)
{
  float		result;

  result = 0;
  while ((int)pos.y >= 0 && (int)pos.x >= 1 && (int)pos.y < mapSize.y &&
	 (int)pos.x < mapSize.x && map->map[(int)pos.y][(int)pos.x] != 1
	 && map->map[(int)pos.y][(int)pos.x] != 4)
    {
      pos = move_forward(pos, - direction, 0.05, map);
      result += 0.05;
    }
  pos = move_forward(pos, - direction, - 0.05, map);
  result -= 0.05;
  while ((int)pos.y >= 0 && (int)pos.x >= 1 && (int)pos.y < mapSize.y &&
	 (int)pos.x < mapSize.x && map->map[(int)pos.y][(int)pos.x] != 1
	 && map->map[(int)pos.y][(int)pos.x] != 4)
    {
      pos = move_forward(pos, - direction, 0.01, map);
      result += 0.01;
    }
  if (map->map[(int)pos.y][(int)pos.x] == 1)
    map->map[(int)pos.y][(int)pos.x] = 4;
  return (result);
}

