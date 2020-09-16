/*
** move_forward.c for bswolf3d in /home/angevil124/prog/graphical/bswolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Dec 15 09:08:56 2016 benoit
** Last update Fri Feb  3 13:06:55 2017 Benoit
*/

#include <math.h>
#include "fcts_and_strcts.h"

sfVector2f	move_forward(sfVector2f pos, float direction,
			     float distance, t_map *map)
{
  float		factor_x;
  float		factor_y;

  direction = direction * M_PI / 180;
  factor_x = distance * cos(direction);
  factor_y = distance * sin(direction);
  if ((int)(pos.x + factor_x) <= map->map[0][0] && (int)(pos.x + factor_x) >= 1
      && (int)(pos.y + factor_y) < map->row && (int)(pos.y + factor_y) >= 0)
    {
      pos.x = pos.x + factor_x;
      pos.y = pos.y + factor_y;
    }
  return (pos);
}
