/*
** intersect_plane.c for bsraytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb  7 14:49:34 2017 Benoit
** Last update Tue Feb 14 11:45:41 2017 Benoit
*/

#include "framebuffer.h"

sfVector3f	get_normal_plane(int upward)
{
  sfVector3f	result;

  result.x = 0;
  result.y = 0;
  result.z = 1;
  if (upward == 0)
    result.z = - 1;
  return (result);
}

float	intersect_plane(sfVector3f eye_pos, sfVector3f dir_vector)
{
  float	k;

  if (dir_vector.z == 0.0)
    return (- 1.0);
  k = (- eye_pos.z) / dir_vector.z;
  if (k < 0.0)
    return (- 1.0);
  return (k);
}
