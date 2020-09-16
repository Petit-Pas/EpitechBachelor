/*
** raycast.c for bswolf3d in /home/angevil124/prog/graphical/bswolf3d/src
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Dec 15 09:31:44 2016 benoit
** Last update Wed Jan 25 11:47:51 2017 Benoit
*/

#include "fcts_and_strcts.h"

float	raycast(sfVector2f pos, float direction,
		int **map, sfVector2i mapSize)
{
  float		result;

  result = 0;
  while ((int)pos.y >= 0 && (int)pos.x >= 1 && (int)pos.y < mapSize.y &&
	 (int)pos.x < mapSize.x && map[(int)pos.y][(int)pos.x] != 1)
    {
      pos = move_forward(pos, - direction, 0.005);
      result += 0.005;
    }
  return (result);
}

