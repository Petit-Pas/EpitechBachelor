/*
** cylinder.c for raytracer1 in /home/angevil124/prog/graphical/raytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb 14 09:35:47 2017 Benoit
** Last update Mon Mar 13 08:28:12 2017 Benoit
*/

#include <math.h>
#include "framebuffer.h"

sfVector3f	get_normal_cylinder(sfVector3f intersection_point,
				    float useless, int useless2)
{
  sfVector3f	result;

  (void)useless;
  (void)useless2;
  result.z = 0;
  result.x = intersection_point.x;
  result.y = intersection_point.y;
  return (result);
}

float	intersect_cylinder(sfVector3f eye_pos,
			 sfVector3f dir_vector, float radius)
{
  float	a;
  float	b;
  float	c;
  float delta;
  float	result;

  a = pow(dir_vector.x, 2) + pow(dir_vector.y, 2);
  b = 2 * (eye_pos.x * dir_vector.x + eye_pos.y * dir_vector.y);
  c = pow(eye_pos.x, 2) + pow(eye_pos.y, 2) - pow(radius, 2);
  delta = pow(b, 2) - (4 * a * c);
  if (a == 0)
    return (- 1.0);
  if (delta < 0.0)
    return (- 1.0);
  if (delta == 0)
    {
      result = - b / (2 * a);
      if (result < 0.0)
	return (- 1.0);
      return (result);
    }
  return (do_hard(a, b, delta));
}
