/*
** calc_dir_vector.c for bsraytracer1 in /home/angevil124/prog/graphical/bsraytracer1
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb  7 13:43:05 2017 Benoit
** Last update Mon Mar 13 07:40:50 2017 Benoit
*/

#include <math.h>
#include "framebuffer.h"

sfVector3f	calc_dir_vector(float dist_to_plane, sfVector2i screen_size,
				sfVector2i screen_pos)
{
  sfVector3f	result;

  result.x = dist_to_plane;
  result.y = (screen_size.x / 2) - screen_pos.x;
  result.z = (screen_size.y / 2) - screen_pos.y;
  return (result);
}
