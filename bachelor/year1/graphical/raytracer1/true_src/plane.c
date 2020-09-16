/*
** intersect_plane.c for bsraytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb  7 14:49:34 2017 Benoit
** Last update Mon Mar 13 08:34:26 2017 Benoit
*/

#include "framebuffer.h"

sfVector3f	get_normal_plane(sfVector3f useless,
				 float useless2,
				 int upward)
{
  sfVector3f	result;

  (void)useless;
  (void)useless2;
  result.x = 0;
  result.y = 0;
  result.z = 1;
  if (upward == 0)
    result.z = - 1;
  return (result);
}

float	intersect_plane(sfVector3f eye_pos,
			sfVector3f dir_vector, float useless)
{
  float	k;

  (void)useless;
  if (dir_vector.z == 0.0)
    return (- 1.0);
  k = (- eye_pos.z) / dir_vector.z;
  if (k < 0.0)
    return (- 1.0);
  return (k);
}
